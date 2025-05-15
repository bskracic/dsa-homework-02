#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <optional>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game of Life");
	window.setFramerateLimit(10);

	sf::Font font;
	if (!font.openFromFile("C:/Windows/Fonts/BAUHS93.TTF")) {
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Resources/Neon_Purple.png")) {
		std::cout << "Failed to load background texture"<<std::endl;
		return -1;
	}
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale(sf::Vector2f(
		window.getSize().x / static_cast<float>(backgroundTexture.getSize().x),
		window.getSize().y / static_cast<float>(backgroundTexture.getSize().y)
	));



	bool paused = false;

	sf::Text title(font, "Game of Life", 50);
	title.setFillColor(sf::Color::White);

	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin({ bounds.getCenter().x, 0.f });
	title.setPosition({ window.getSize().x / 2.f, 20.f });


	sf::Text instructions(font, "P - Pause / Resume      R - Reset Grid      Esc - Exit", 26);
	instructions.setFillColor(sf::Color(180, 180, 180));
	instructions.setPosition({ 160.f, 80.f });

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
					std::cout << "Grid reset" << std::endl;
				}
				else if (key->scancode == sf::Keyboard::Scan::Escape) {
					std::cout << "Goodbye!" << std::endl;
					window.close(); 
				}
			}



		}


		window.clear();
		sf::RectangleShape headerBar;
		headerBar.setSize(sf::Vector2f(window.getSize().x, 80));
		headerBar.setFillColor(sf::Color(20, 20, 20));
		window.draw(backgroundSprite);  
		window.draw(headerBar);

		window.draw(title);
		game.draw(paused);
		window.draw(instructions);
		if (paused) {
			sf::Text pausedText(font, "PAUSED", 48);
			pausedText.setFillColor(sf::Color(255, 255, 255, 190));
			sf::FloatRect bounds = pausedText.getLocalBounds();
			pausedText.setOrigin(bounds.position + bounds.size / 2.f);
			pausedText.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });


			window.draw(pausedText);
		}
		if (!paused) {
			game.next_generation();
		}
		window.display();

	}


	return 0;
}
