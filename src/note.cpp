#include <vector>
#include <SFML/Graphics.hpp>

#include "note.h"



void addNote(int pisteID, std::vector<sf::CircleShape> &pistes,
            std::vector<Note> &Notes, 
            std::vector<sf::CircleShape> &Shapes, 
            float realTime)
{

    sf::CircleShape piste = pistes.at(pisteID);
    Note note(300, piste.getPosition().x, realTime);
    Notes.push_back(note);
    Shapes.push_back(sf::CircleShape(50));
}
