#include <vector>
#include <SFML/Graphics.hpp>


void addNote(sf::CircleShape &piste, std::vector<Note> &Notes, std::vector<sf::CircleShape> &Shapes){

    std::cout << piste.getPosition().x << std::endl;
    Note note(300,0, piste.getPosition().x);
    Notes.push_back(note);
    Shapes.push_back(sf::CircleShape(50));
}
