#include <vector>
#include <SFML/Graphics.hpp>

void checkHitNote(std::vector<Note> &Notes, sf::CircleShape piste, 
                std::vector<sf::CircleShape> &Shapes, 
                sf::Text &texte, sf::Sound &hitsound);

void keyPressedCases(sf::Event evnt, 
                    sf::Music &music, 
                    std::vector<Note> &allActiveNotes,
                    std::vector<sf::CircleShape> &allPiste,
                    std::vector<sf::CircleShape> &allActiveShapes, 
                    sf::Text &texte, sf::Sound &hitsound);

void keyReleasedCases(sf::Event evnt, 
                    std::vector<sf::CircleShape> &allPiste);