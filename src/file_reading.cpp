#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Audio.hpp>

#include "note.h"

void readFromFile(int songID, float &bpm, float &offset,
                std::vector<sf::CircleShape> &Pistes,
                std::vector<Note> &Notes, 
                std::vector<sf::CircleShape> &Shapes)
{

    std::string str_songID = std::to_string(songID);

    std::string filename = "songs/" + str_songID + "/map_data.ppp";
   
    std::ifstream myfile;
    
    int line = 0;

    myfile.open(filename.c_str());
    if (myfile.fail())
    {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string tp;

    while(std::getline(myfile, tp) && tp != "$")
    { 
        (line==0) ? bpm = atof(tp.c_str()) : offset = atof(tp.c_str());
        line++;
    }

    while(std::getline(myfile, tp) && tp != "")
    { 
        int delimiter = tp.find_first_of(":");

        float realTime = atof(tp.substr(0,delimiter).c_str()) - offset;
        int desiredPiste = atof(tp.substr(delimiter+1,1).c_str());

        addNote(desiredPiste, Pistes, Notes, Shapes, realTime);
        

    }
}

void findSong(int songID, sf::Music &music){
    //Loading de la musique + gestion erreur

    std::string str_songID = std::to_string(songID);
    std::string filename = "songs/audio/" + str_songID + ".wav";

    if (!music.openFromFile(filename.c_str())){
        std::cout << "ERROR: Loading Song " << std::endl;
    }


}