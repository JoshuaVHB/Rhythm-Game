#include <vector>
#include <SFML/Graphics.hpp>

class Note
{

    public:
    float pos_x;
    float pos_y;
    float speed;

    Note* nextNote = nullptr;

    Note(float speed = 200, float y = 0  ,int side = 0 /*Numéro de piste*/){
        this->speed = speed;
        this->pos_y = y;
        (side==0) ? this->pos_x = 12 : this->pos_x=400;
    }

    void update(float deltaTime){
        //std::cout << this->pos_y << std::endl;
        this->pos_y += this->speed * deltaTime;
    }

    void setNextNote(Note* nextNote){
        this->nextNote = nextNote;
    }
    
};
