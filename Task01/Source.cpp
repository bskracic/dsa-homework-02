#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <optional>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game of Life");
    window.setFramerateLimit(10);

    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/consola.ttf")) {
        std::cout << "Failed to load font\n";
        return -1;
    }

    
    sf::Text title(font, "Game of Life", 42);
    title.setFillColor(sf::Color::White);

    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin({ bounds.getCenter().x, 0.f });  
    title.setPosition({ window.getSize().x / 2.f, 20.f });

    game_of_life game;
    game.set_window(&window);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(title);       
        game.draw();
        game.next_generation();
        window.display();
    }

    return 0;
}
