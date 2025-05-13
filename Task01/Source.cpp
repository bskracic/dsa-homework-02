#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Game of Life");
    window.setFramerateLimit(10); // slows down generations

    game_of_life game;
    game.set_window(&window); // assign window to game logic

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        game.draw();           // draw current generation
        game.next_generation(); // compute next generation
        window.display();
    }

    return 0;
}
