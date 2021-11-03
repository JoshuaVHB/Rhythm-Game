#include <vector>
#include <SFML/Graphics.hpp>

#include "note.h"
#include "input.h"

void checkHitNote(std::vector<Note> &Notes, sf::CircleShape piste, std::vector<sf::CircleShape> &Shapes, sf::Text &texte, sf::Sound &hitsound){

    float p_x = piste.getPosition().x;
    float p_y = piste.getPosition().y;

    for (int i = 0; i<(int)Notes.size();i++){

        if (Notes[i].pos_x!=p_x || Notes[i].pos_y<300) {continue;}

        if (Notes[i].pos_y+10>p_y-10 && Notes[i].pos_y-10<p_y+10){
            hitsound.play();
            texte.setString("300");
        }
        
        else if (Notes[i].pos_y+30>p_y-30 && Notes[i].pos_y-30<p_y+30){
            hitsound.play();
            texte.setString("100");
        }
        else if (Notes[i].pos_y+50>p_y-50 && Notes[i].pos_y-50<p_y+50){
            hitsound.play();
            texte.setString("50");
        }
        else {
            texte.setString("X");
        }


        Notes.erase(Notes.begin() + i);
        Shapes.erase(Shapes.begin() + i);
        i--;
        break;
    }

}

void keyPressedCases(sf::Event evnt, 
                    sf::Music &music, 
                    std::vector<Note> &allActiveNotes,
                    std::vector<sf::CircleShape> &allPiste,
                    std::vector<sf::CircleShape> &allActiveShapes,
                    sf::Text &texte, sf::Sound &hitsound){

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
        if (music.getStatus() == sf::SoundSource::Status::Playing){
            music.pause();
        } 
        else {
            music.play();
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

}

void keyReleasedCases(sf::Event evnt, 
                    std::vector<sf::CircleShape> &allPiste)
{
    if (sf::Keyboard::Key::G == evnt.key.code){

        sf::CircleShape &piste = allPiste.at(0);
        piste.setFillColor(sf::Color(255,0,0));
    }

    if (sf::Keyboard::Key::H == evnt.key.code){

        sf::CircleShape &piste = allPiste.at(1);
        piste.setFillColor(sf::Color(255,0,0));
    }

    if (sf::Keyboard::Key::L == evnt.key.code){

        sf::CircleShape &piste = allPiste.at(2);
        piste.setFillColor(sf::Color(0,0,255));
    }

    if (sf::Keyboard::Key::M == evnt.key.code){

        sf::CircleShape &piste = allPiste.at(3);
        piste.setFillColor(sf::Color(0,0,255));
    }


}