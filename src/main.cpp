#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>


#include "time.h"
#include "note.h"
#include "piste.h"
#include "input.h"
#include "file_reading.h"



int main(){

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Prototype", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(240);

    sf::Clock deltaClock;
    float deltaTime;

    int songID = 2;
    float bpm; 
    float offset;

    sf::Music music;  
    findSong(songID, music);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("songs/audio/hitsound.wav")){
        return -1;
    }

    sf::Sound hitsound;
    hitsound.setBuffer(buffer);


    std::vector<Note> allActiveNotes;
    std::vector<sf::CircleShape> allActiveShapes;
    std::vector<sf::CircleShape> allPiste; //Représente les pos_x

    addPistes(allPiste);

    readFromFile(songID, bpm, offset, allPiste ,allActiveNotes, allActiveShapes);


    float crotchet = 60/bpm; //The duration of a beat
    // sf::Time duration = music.getDuration(); Song duration
    sf::Time songposition = music.getPlayingOffset(); //Actual pos in the song
    float songposition_ms = 0;
    float timeBeforeNextBeat = 0;
    int beatNumber = 0;


    sf::Font font;
    if (!font.loadFromFile("src/arial.ttf"))
    {
    return -1;
    }

    sf::Text texte;
    texte.setFont(font);
    texte.setPosition(0,0);
    texte.setCharacterSize(24);
    texte.setFillColor(sf::Color::Red);
    texte.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Couleurs pour le background
    float R = 100.0f;
    float G = 100.0f;
    float B = 100.0f;
    

    // Boucle du jeu
    while (window.isOpen())
    {

        deltaTime = deltaClock.restart().asSeconds();
        sf::Event evnt;

        while (window.pollEvent(evnt))
        {

            switch (evnt.type){

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    keyPressedCases(evnt, music, allActiveNotes,allPiste, allActiveShapes, texte, hitsound);
                    break;

                case sf::Event::KeyReleased:
                    keyReleasedCases(evnt, allPiste);
                    break;
                
                default:
                    break;
            }
        }
            
        songposition = music.getPlayingOffset(); //Actual pos in the song
        songposition_ms = songposition.asMilliseconds(); // Explicite
        timeBeforeNextBeat = songposition_ms + offset - (crotchet * beatNumber * 1000); //Same

        if (timeBeforeNextBeat > crotchet*1000 && songposition_ms > offset){ // Metronome !! Commence à partir de Offset et se répète à chaque beat
            beatNumber ++;
            timeBeforeNextBeat = 0;
            if (R<=100 && beatNumber%4==0){ //Effet de style (flashy bg) tous les 4 beats

                R = 200;
                G = 200;
                B = 200;
            }
        }

        if (R>100){ // Fondu après le beat
            R -=crotchet; 
            G -=crotchet; 
            B -=crotchet;
        }

        window.clear(sf::Color(R,G,B)); // On dessine tout

        for (sf::CircleShape& piste : allPiste){
            window.draw(piste);
        }

        for (int i = 0; i<(int)allActiveShapes.size(); i++){
            
            if (songposition_ms > allActiveNotes[i].spawningTime){
                allActiveNotes[i].update(deltaTime, music.getStatus());

                if (allActiveNotes[i].pos_y>HEIGHT+50) {
                    allActiveNotes.erase(allActiveNotes.begin() + i);
                    allActiveShapes.erase(allActiveShapes.begin() + i);
                    i--;
                    texte.setString("X");
                    continue;
                }
                allActiveShapes[i].setPosition(allActiveNotes[i].pos_x, allActiveNotes[i].pos_y);
                window.draw(allActiveShapes[i]);
            }
        }

        window.draw(texte);
        window.display();
    }
    
    return 0;
}