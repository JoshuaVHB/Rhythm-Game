#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define WIDTH 1024
#define HEIGHT 700



void addPistes( std::vector<sf::CircleShape> &allPistes){

    int radius = 50;
    
    int offset_x_gauche = WIDTH * 10/100;
    int offset_x_droite = WIDTH * 10/100;
    int offset_y_bas = HEIGHT * 10/100;



    for (int i=0; i<4;i++){
        sf::CircleShape piste(radius);

        std::cout << "Offset gauche" << offset_x_gauche << std::endl;
        std::cout << "Radius : " << radius << std::endl;
        std::cout << "(i * (WIDTH - offset_x_droite) / 4) : " << (i * (WIDTH - offset_x_droite) / 4) << std::endl;

        int pos_x = offset_x_gauche + radius + (i * (WIDTH - offset_x_droite) / 4) - offset_x_droite/2;
        int pos_y = HEIGHT - offset_y_bas - radius;

        sf::Color color;
        sf::Color outline_color;

        if (pos_x < WIDTH / 2){
            color = sf::Color(255,0,0);
            outline_color = sf::Color(100,0,0);

        } else {
            color = sf::Color(0,0,255); 
            outline_color = sf::Color(0,0,100);
        }


        piste.setFillColor(color);
        piste.setOutlineColor(outline_color);
        piste.setOutlineThickness(-10);


        piste.setPosition(pos_x , pos_y);
        allPistes.push_back(piste);
    }



}
