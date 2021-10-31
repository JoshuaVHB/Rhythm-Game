#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "time.h"

#define SPAWN_Y 0
#define RADIUS 50

class Note
{

    public:
    float pos_x;
    float pos_y;
    float speed;
    float realTime;
    float spawningTime;

    Note(float speed = 200, float x = 0, float realTime = 0 /*Numéro de piste*/){
        this->speed = speed;
        this->pos_y = SPAWN_Y;
        this->pos_x = x;
        this->realTime = realTime;
        this->spawningTime = calculateSpawningTime(this->realTime);
    }

    void update(float deltaTime, float songPosition){
        //std::cout << this->pos_y << std::endl;
        // y = h*(t - to / d)
        // h = distance spawn - centre de la note 
        // to = tm - d 
        // d est le temps sur le screen (en  fonction  de  speed)

        
        float offset_y = HEIGHT * 0.9 - RADIUS;
        float h = offset_y - SPAWN_Y;
        float vel = deltaTime * 1000 *h / (this->realTime - this->spawningTime) ;
        this->pos_y += vel;

    }
};

void addNote(int pisteID, std::vector<sf::CircleShape> &pistes, std::vector<Note> &Notes, std::vector<sf::CircleShape> &Shapes, float realTime);
