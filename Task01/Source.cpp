#include <SFML/Graphics.hpp>
<<<<<<< HEAD

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
=======
#include <iostream>
#include <string>
#include <fstream>
#include "game_of_life.h"
using namespace std;
int main()
{
    
        game_of_life the_game;

        bool dalje;
        do {
            the_game.iscrtaj();
            the_game.sljedeca_generacija();

            cout << "Dalje (1/0): ";
            cin >> dalje;
        } while (dalje);

        return 0;
    }
>>>>>>> 7833747 (DZ02)
