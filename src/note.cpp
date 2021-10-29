#include <vector>
#include <SFML/Graphics.hpp>

#include "note.h"



void addNote(sf::CircleShape &piste, std::vector<Note> &Notes, std::vector<sf::CircleShape> &Shapes, float realTime){

    Note note(300, piste.getPosition().x, realTime);
    Notes.push_back(note);
    Shapes.push_back(sf::CircleShape(50));
}
