#include <vector>
#include <SFML/Graphics.hpp>


void addNote(int piste, std::vector<Note> &Notes, std::vector<sf::CircleShape> &Shapes){

    Note note(300,0, piste);
    Notes.push_back(note);
    Shapes.push_back(sf::CircleShape(50));
}
