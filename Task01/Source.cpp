#include <SFML/Graphics.hpp>
#include "IgraZivota.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Hello, SFML world!");
	window.setFramerateLimit(60);
	IgraZivota igra_zivota(&window, 800 / 8, 600 / 8, 8);

	sf::Clock clock;

	while (window.isOpen())
	{
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() > 2)

			window.clear();
		igra_zivota.draw();
		window.display();
		clock.restart();
	}

	return 0;
}