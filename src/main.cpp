#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>



#define WIDTH 512
#define HEIGHT 512

class Note
{

    public:
    float pos_x;
    float pos_y;
    float speed;

    Note* nextNote = nullptr;

    Note(float speed = 5){
        this->speed = speed;
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
    Note note = Note();

    note.pos_x = 12;
    note.pos_y = 0;

    Note note2 = Note();

    note2.pos_x = 400;
    note2.pos_y = 0;

    Note note3 = Note();

    note3.pos_x = 400;
    note3.pos_y = 0;

    Note note4 = Note();
    note4.pos_x = 12;
    note4.pos_y = -100;

    note.setNextNote(&note4);
    note2.setNextNote(&note3);

    sf::CircleShape shape(50);
    sf::CircleShape shape2(50);
    sf::CircleShape shape3(50);
    sf::CircleShape shape4(50);

    Note* tabNotesGauche[10] = {0};
    tabNotesGauche[0] = &note;

    Note* tabNotesDroite[10] = {0};
    tabNotesDroite[0] = &note2;

    sf::CircleShape* tabShapesG[10];
    tabShapesG[0] = &shape;
    tabShapesG[1] = &shape4;

    sf::CircleShape* tabShapesD[10];
    tabShapesD[0] = &shape2;
    tabShapesD[1] = &shape3;


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



                        for (int i = 0; i<1;i++){
                            Note* actualNoteG = tabNotesGauche[i];
                            if (actualNoteG->pos_y+10>390 && actualNoteG->pos_y-10<410){
                                std::cout << "300 GAUCHE" << std::endl;
                            }
                            else if (actualNoteG->pos_y+30>370 && actualNoteG->pos_y-30<430){
                                std::cout << "100 GAUCHE" << std::endl;
                            }
                            else if (actualNoteG->pos_y+50>350 && actualNoteG->pos_y-50<450){
                                std::cout << "50 GAUCHE" << std::endl;
                            }
                            else {
                                std::cout << "what GAUCHE" << std::endl;
                            }
                        }
                    }

                    if (sf::Keyboard::Key::L == evnt.key.code){
                        droite.setFillColor(sf::Color(0,0,130));

                        for (int i = 0; i<1;i++){
                            Note* actualNote = tabNotesDroite[i];
                            if (actualNote->pos_y+10>390 && actualNote->pos_y-10<410){
                                std::cout << "300 DROITE" << std::endl;
                                
                            }
                            else if (actualNote->pos_y+30>370 && actualNote->pos_y-30<430){
                                std::cout << "100 DROITE" << std::endl;
                            }
                            else if (actualNote->pos_y+50>350 && actualNote->pos_y-50<450){
                                std::cout << "50 DROITE" << std::endl;
                            }
                            else {
                                std::cout << "miss DROITE" << std::endl;
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

        Note* noteG = tabNotesGauche[0];
        sf::CircleShape* ptrShapeG;

        Note* noteD = tabNotesDroite[0];
        sf::CircleShape* ptrShapeD;

        int j = 0;

        do{
            ptrShapeG = tabShapesG[j];
             sf::CircleShape shapeG = *ptrShapeG;

             noteG->update();

             shapeG.setPosition(noteG->pos_x, noteG->pos_y);
             window.draw(shapeG);
             noteG = noteG->nextNote;
             j++;
             ptrShapeG = tabShapesG[j];
        }
        while (noteG->nextNote!=nullptr);

        j = 0;

        do{
            ptrShapeD = tabShapesD[j];
            sf::CircleShape shapeD = *ptrShapeD;

            noteD->update();
            shapeD.setPosition(noteD->pos_x, noteD->pos_y);
            window.draw(shapeD);
            noteD = noteD->nextNote;
            j++;
            ptrShapeD = tabShapesD[j];
        }
        while (noteD->nextNote!=nullptr);

        window.display();
    }
    
    return 0;
}