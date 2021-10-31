#include <iostream>
#include <fstream>
#include <string>

#include "note.h"

void readFromFile(int mapId, float &bpm, float &offset,
                std::vector<sf::CircleShape> &Pistes,
                std::vector<Note> &Notes, 
                std::vector<sf::CircleShape> &Shapes)
{


    std::string filename = "songs/pipi.ppp";
   
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

    while(std::getline(myfile, tp))
    { 
        int strSize = tp.size();
        int delimiter = tp.find_first_of(":");

        
        std::cout << "STRsIZE : " << strSize << std::endl;
        std::cout << "DEL : " << delimiter << std::endl;

        float realTime = atof(tp.substr(0,delimiter).c_str());

        std::cout <<" WHAT : " << tp.substr(delimiter+1,1).c_str() << std::endl;

        int desiredPiste = atof(tp.substr(delimiter+1,1).c_str());

        std::cout << "realTime : " << realTime << std::endl;
        std::cout << "piste : " << desiredPiste << std::endl;

        addNote(desiredPiste, Pistes, Notes, Shapes, realTime);
        

    }
}