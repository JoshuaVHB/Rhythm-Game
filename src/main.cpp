#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


#include "time.h"
#include "note.h"
#include "piste.h"
#include "input.h"



int main(){

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Prototype", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock deltaClock;
    float deltaTime;

    //Loading de la musique + gestion erreur
    sf::Music music;
    if (!music.openFromFile("audio/1.wav")){
        std::cout << "ERROR: Loading Song " << std::endl;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("audio/hitsound.wav")){
        return -1;
    }

    sf::Sound hitsound;
    hitsound.setBuffer(buffer);


    window.setFramerateLimit(240);

    //ALED

    std::vector<Note> allActiveNotes;
    std::vector<sf::CircleShape> allActiveShapes;
    std::vector<sf::CircleShape> allPiste; //Représente les pos_x

    addPistes(allPiste);

    float bpm = 200; 
    float crotchet = 60/bpm; //The duration of a beat
    sf::Time duration = music.getDuration(); // Song duration
    sf::Time songposition = music.getPlayingOffset(); //Actual pos in the song
    float m_seconds = 0;
    float timeBeforeNextBeat = 0;
    int beatNumber = 0;
    float offset = 1788;

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
    
    // On lance la musique au départ puis on déclare qu'elle son statut (playing)
    music.play();
    sf::SoundSource::Status status = sf::SoundSource::Status::Playing;


    


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

                    /* Gestion du volume avec les flèches */
                    if (sf::Keyboard::Key::Up == evnt.key.code){
                        int vol = music.getVolume();
                        (vol <100) ? music.setVolume(vol+5) : music.setVolume(vol);
                    }
                    if ( sf::Keyboard::Key::Down == evnt.key.code){
                        int vol = music.getVolume();
                        (vol >0) ? music.setVolume(vol-5) : music.setVolume(vol) ;

                    }

                    /* Pause ou resume de la musique avec espace */
                    if (sf::Keyboard::Key::Space == evnt.key.code){
                        if (status == sf::SoundSource::Status::Playing){
                            music.pause();
                            status = sf::SoundSource::Status::Paused;
                        } 
                        else if (status == sf::SoundSource::Status::Paused){
                            music.play();
                            status = sf::SoundSource::Status::Playing;
                        }
                    }


                    /* Gestion des input des joueurs */
                    if (sf::Keyboard::Key::G == evnt.key.code){ 
                        
                        
                        sf::CircleShape &piste = allPiste.at(0);
                        piste.setFillColor(sf::Color(130,0,0));
                        checkHitNote(allActiveNotes, piste, allActiveShapes, texte,  hitsound);

                    }


                    if (sf::Keyboard::Key::H == evnt.key.code){ 
                        
                        
                        sf::CircleShape &piste = allPiste.at(1);
                        piste.setFillColor(sf::Color(130,0,0));
                        checkHitNote(allActiveNotes, piste, allActiveShapes, texte,  hitsound);

                    }


                    if (sf::Keyboard::Key::L == evnt.key.code){

                        sf::CircleShape &piste = allPiste.at(2);
                        piste.setFillColor(sf::Color(0,0,130));
                        checkHitNote(allActiveNotes, piste, allActiveShapes, texte,  hitsound);
                            
                    }

                    if (sf::Keyboard::Key::M == evnt.key.code){

                        sf::CircleShape &piste = allPiste.at(3);
                        piste.setFillColor(sf::Color(0,0,130));
                        checkHitNote(allActiveNotes, piste, allActiveShapes, texte,  hitsound);
                            
                    }

                    //std::cout << m_seconds << std::endl;

                    break;

                /* On release */
                case sf::Event::KeyReleased:

                    if (sf::Keyboard::Key::G == evnt.key.code){

                        sf::CircleShape &piste = allPiste.at(0);
                        piste.setFillColor(sf::Color(255,0,0));
                        break;
                    }

                    if (sf::Keyboard::Key::H == evnt.key.code){

                        sf::CircleShape &piste = allPiste.at(1);
                        piste.setFillColor(sf::Color(255,0,0));
                        break;
                    }

                    if (sf::Keyboard::Key::L == evnt.key.code){

                        sf::CircleShape &piste = allPiste.at(2);
                        piste.setFillColor(sf::Color(0,0,255));
                        break;
                    }

                    if (sf::Keyboard::Key::M == evnt.key.code){

                        sf::CircleShape &piste = allPiste.at(3);
                        piste.setFillColor(sf::Color(0,0,255));
                        break;
                    }

                    break;
            }
        }
            

        songposition = music.getPlayingOffset(); //Actual pos in the song
        m_seconds = songposition.asMilliseconds(); // Explicite
        timeBeforeNextBeat = m_seconds + offset - (crotchet * beatNumber * 1000); //Same


        if (timeBeforeNextBeat > crotchet*1000 && m_seconds > offset){ // Metronome !! Commence à partir de Offset et se répète à chaque beat
            beatNumber ++;
            timeBeforeNextBeat = 0;

            int index = rand() % 4 ;
            float randomtiming = beatNumber * crotchet * 1000 + offset ;
            sf::CircleShape &test = allPiste.at(index);
            addNote(test, allActiveNotes, allActiveShapes, randomtiming);

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
            
            if (m_seconds > allActiveNotes[i].spawningTime){
                allActiveNotes[i].update(deltaTime, m_seconds);

                if (allActiveNotes[i].pos_y>HEIGHT+50) {
                    allActiveNotes.erase(allActiveNotes.begin() + i);
                    allActiveShapes.erase(allActiveShapes.begin() + i);
                    i--;
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