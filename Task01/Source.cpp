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

	bool paused = false;

	sf::Text title(font, "Game of Life", 42);
	title.setFillColor(sf::Color::White);

	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin({ bounds.getCenter().x, 0.f });
	title.setPosition({ window.getSize().x / 2.f, 20.f });


	sf::Text instructions(font, "P - Pause / Resume     R - Reset Grid     Esc - Exit", 24);
	instructions.setFillColor(sf::Color(180, 180, 180));
	instructions.setPosition({ 50.f, 80.f });

	game_of_life game;
	game.set_window(&window);

	while (window.isOpen())
	{
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::KeyPressed>()) {
				const auto* key = event->getIf<sf::Event::KeyPressed>();
				if (!key) continue;

				if (key->scancode == sf::Keyboard::Scan::P) {
					paused = !paused;
					std::cout << (paused ? "Paused\n" : "Resumed\n");
				}
				else if (key->scancode == sf::Keyboard::Scan::R) {
					game.reset();
					std::cout << "Grid reset\n";
				}
				else if (key->scancode == sf::Keyboard::Scan::Escape) {
					window.close(); 
				}
			}



		}


		window.clear();
		window.draw(title);
		game.draw();
		window.draw(instructions);
		if (!paused) {
			game.next_generation();
			window.display();
		}
	}


	return 0;
}
