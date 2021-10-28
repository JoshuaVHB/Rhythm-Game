#include <vector>
#include <SFML/Graphics.hpp>

class Note
{

    public:
    float pos_x;
    float pos_y;
    float speed;

    Note* nextNote = nullptr;

    Note(float speed = 200, float y = 0  ,float x = 0 /*Numéro de piste*/){
        this->speed = speed;
        this->pos_y = y;
        this->pos_x = x;
    }

    void update(float deltaTime){
        //std::cout << this->pos_y << std::endl;
        // y = h*(t - to / d)
        // h = distance spawn - centre de la note 
        // to = tm - d 
        // d est le temps sur le screen (en  fonction  de  speed)
        this->pos_y += this->speed * deltaTime;
    }

};
