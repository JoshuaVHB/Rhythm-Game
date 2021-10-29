#include <vector>
#include <SFML/Graphics.hpp>

void checkHitNote(std::vector<Note> &Notes, sf::CircleShape piste, std::vector<sf::CircleShape> &Shapes, sf::Text &texte, sf::Sound hitsound){

    float p_x = piste.getPosition().x;
    float p_y = piste.getPosition().y;

    for (int i = 0; i<Notes.size();i++){

        if (Notes[i].pos_x!=p_x) {continue;}

        if (Notes[i].pos_y+10>p_y-10 && Notes[i].pos_y-10<p_y+10){
            hitsound.play();
            texte.setString("300");
        }
        
        else if (Notes[i].pos_y+30>p_y-30 && Notes[i].pos_y-30<p_y+30){
            hitsound.play();
            texte.setString("100");
        }
        else if (Notes[i].pos_y+50>p_y-50 && Notes[i].pos_y-50<p_y+50){
            hitsound.play();
            texte.setString("50");
        }
        else {
            texte.setString("X");
        }


        Notes.erase(Notes.begin() + i);
        Shapes.erase(Shapes.begin() + i);
        i--;
        break;
    }

}