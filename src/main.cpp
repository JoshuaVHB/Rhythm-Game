#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>



#define WIDTH 512
#define HEIGHT 512

class Note
{

    public:
    float pos_x;
    float pos_y;
    float speed;

    Note* nextNote = nullptr;

    Note(float speed = 5, int side = 0 /*GAUCHE = 0, DROITE = 1*/){
        this->speed = speed;
        (side==0) ? this->pos_x = 12 : this->pos_x=400;
    }

    void update(){
        //std::cout << this->pos_y << std::endl;
        this->pos_y += this->speed * 0.01;
    }

    void setNextNote(Note* nextNote){
        this->nextNote = nextNote;
    }
    
};

int main(){

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Prototype", sf::Style::Titlebar | sf::Style::Close);

    //Loading de la musique + gestion erreur
    sf::Music music;
    if (!music.openFromFile("audio/1.wav")){
        std::cout << "ERROR: Loading Song " << std::endl;
    }

    //ALED

    std::vector<Note> allActiveNotes;
    allActiveNotes.push_back({3,0});
    allActiveNotes.push_back({3,1});


    //ALED


    std::vector<sf::CircleShape> allActiveShapes;
    allActiveShapes.push_back(sf::CircleShape(50));
    allActiveShapes.push_back(sf::CircleShape(50));


    //Création des formes (censées représenter des boutons lol)
    sf::CircleShape gauche(50,50);
    gauche.setFillColor(sf::Color(255,0,0));
    gauche.setOutlineColor(sf::Color(100,0,0));
    gauche.setOutlineThickness(-10);
    gauche.setPosition(12,400);

    sf::CircleShape droite(50,50);
    droite.setFillColor(sf::Color(0,0,255));
    droite.setOutlineColor(sf::Color(0,0,100));
    droite.setOutlineThickness(-10);
    droite.setPosition(400,400);


    float bpm = 200; 
    float crotchet = 60/bpm; //The duration of a beat
    sf::Time duration = music.getDuration(); // Song duration
    sf::Time songposition = music.getPlayingOffset(); //Actual pos in the song
    float timeBeforeNextBeat = 0;
    int beatNumber = 0;
    float offset = 1788;

    // Couleurs pour le background
    float R = 100.0f;
    float G = 100.0f;
    float B = 100.0f;
    
    // On lance la musique au départ puis on déclare qu'elle son statut (playing)
    music.play();
    sf::SoundSource::Status status = sf::SoundSource::Status::Playing;

    
    std::cout << allActiveShapes.size() << std::endl;


    // Boucle du jeu
    while (window.isOpen())
    {
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
                    if (sf::Keyboard::Key::J == evnt.key.code){ 
                        gauche.setFillColor(sf::Color(130,0,0));



                        for (int i = 0; i<allActiveNotes.size();i++){

                            if (allActiveNotes[i].pos_x!=12) {continue;}

                            if (allActiveNotes[i].pos_y+10>390 && allActiveNotes[i].pos_y-10<410){
                                std::cout << "300 GAUCHE" << std::endl;
                            }
                            else if (allActiveNotes[i].pos_y+30>370 && allActiveNotes[i].pos_y-30<430){
                                std::cout << "100 GAUCHE" << std::endl;
                            }
                            else if (allActiveNotes[i].pos_y+50>350 && allActiveNotes[i].pos_y-50<450){
                                std::cout << "50 GAUCHE" << std::endl;
                            }
                            else {
                                std::cout << "what GAUCHE" << std::endl;
                            }
                        }
                    }

                    if (sf::Keyboard::Key::L == evnt.key.code){
                        droite.setFillColor(sf::Color(0,0,130));

                        for (int i = 0; i<allActiveNotes.size();i++){

                            if (allActiveNotes[i].pos_x!=400) {continue;}

                            if (allActiveNotes[i].pos_y+10>390 && allActiveNotes[i].pos_y-10<410){
                                std::cout << "300 DROITE" << std::endl;
                            }
                            else if (allActiveNotes[i].pos_y+30>370 && allActiveNotes[i].pos_y-30<430){
                                std::cout << "100 DROITE" << std::endl;
                            }
                            else if (allActiveNotes[i].pos_y+50>350 && allActiveNotes[i].pos_y-50<450){
                                std::cout << "50 DROITE" << std::endl;
                            }
                            else {
                                std::cout << "what DROITE" << std::endl;
                            }
                        }
                            
                    }
                    break;

                /* On release */
                case sf::Event::KeyReleased:

                    if (sf::Keyboard::Key::J == evnt.key.code){
                        gauche.setFillColor(sf::Color(255,0,0));
                        break;
                    }

                    if (sf::Keyboard::Key::L == evnt.key.code){
                        droite.setFillColor(sf::Color(0,0,255));
                        break;
                    }
                    break;
            }
        }
            

        songposition = music.getPlayingOffset(); //Actual pos in the song
        float m_seconds = songposition.asMilliseconds(); // Explicite
        timeBeforeNextBeat = m_seconds + offset - (crotchet * beatNumber * 1000); //Same

        if (timeBeforeNextBeat > crotchet*1000 && m_seconds > offset){ // Metronome !! Commence à partir de Offset et se répète à chaque beat
            beatNumber ++;
            timeBeforeNextBeat = 0;
            if (R<=100 && beatNumber%4==0){ //Effet de style (flashy bg) tous les 4 beats
                R = 200;
                G = 200;
                B = 200;
            }
        }

        if (R>100){ // Fondu après le beat
            R -=crotchet*0.1; 
            G -=crotchet*0.1; 
            B -=crotchet*0.1;
        }

        window.clear(sf::Color(R,G,B)); // On dessine tout

        window.draw(gauche);
        window.draw(droite);

        for (int i = 0; i<allActiveShapes.size(); i++){
            allActiveNotes[i].update();
            allActiveShapes[i].setPosition(allActiveNotes[i].pos_x, allActiveNotes[i].pos_y);
            window.draw(allActiveShapes[i]);

        }


        window.display();
    }
    
    return 0;
}