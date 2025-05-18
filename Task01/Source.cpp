#include <SFML/Graphics.hpp>
#include "game_of_life.h"
#include <optional>
#include <iostream>
#include <SFML/Audio.hpp>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

int main()
{
	bool isMuted = false;


	ma_engine engine;
	if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
		return -1;
	}

	ma_sound music;
	if (ma_sound_init_from_file(
		&engine,
		"march-of-the-troopers.wav",
		MA_SOUND_FLAG_STREAM,
		NULL,
		NULL,
		&music) != MA_SUCCESS)
	{
		std::cerr << "Failed to load music.\n";
		return -1;
	}

	ma_sound_set_looping(&music, MA_TRUE);
	ma_sound_start(&music);



	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game of Life");
	window.setFramerateLimit(5);

	sf::Font font;
	if (!font.openFromFile("C:/Windows/Fonts/BAUHS93.TTF")) {
		std::cout << "Failed to load font\n";
		return -1;
	}

	
	sf::Texture darkTexture;
	if (!darkTexture.loadFromFile("Resources/DarkMode.jpg")) {
		std::cout << "Failed to load dark background texture\n";
		return -1;
	}

	sf::Texture lightTexture;
	if (!lightTexture.loadFromFile("Resources/eva-kedves-1-vader-arrives.jpg")) {
		std::cout << "Failed to load light background texture\n";
		return -1;
	}


	sf::Sprite darkSprite(darkTexture);
	darkSprite.setScale(sf::Vector2f(
		window.getSize().x / static_cast<float>(darkTexture.getSize().x),
		window.getSize().y / static_cast<float>(darkTexture.getSize().y)
	));

	sf::Sprite lightSprite(lightTexture);
	lightSprite.setScale(sf::Vector2f(
		window.getSize().x / static_cast<float>(lightTexture.getSize().x),
		window.getSize().y / static_cast<float>(lightTexture.getSize().y)
	));

	bool darkMode = true;

	sf::Texture cellTexture;
	if (!cellTexture.loadFromFile("Resources/Millennium_Falcon_transparent02.png")) {
		std::cout << "Failed to load cell image\n";
		return -1;
	}
	cellTexture.setSmooth(true);

	sf::Texture tieTexture;
	if (!tieTexture.loadFromFile("Resources/TIE_Fighter_transparent.png")) {
		std::cerr << "Failed to load TIE Fighter texture\n";
		return -1;
	}

	tieTexture.setSmooth(true);


	sf::Texture deadTexture;
	if (!deadTexture.loadFromFile("Resources/Blackhole_transparent.png")) {
		std::cerr << "Failed to load dead cell image\n";
		return -1;
	}
	deadTexture.setSmooth(true);






	bool paused = true;
	bool stepOnce = false;


	sf::Text title(font, "Game of Life", 50);
	title.setFillColor(sf::Color::White);

	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin({ bounds.getCenter().x, 0.f });
	title.setPosition({ window.getSize().x / 2.f, 20.f });


	sf::Text instructions(font, " P - Play / Pause      N - Next Step      R - Reset Grid      I - Icon Mode      L - Light/Dark Mode      M - Mute      Esc - Exit", 26);

	instructions.setPosition({ 180.f, 80.f });

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
					std::cout << "Goodbye!\n";
					window.close();
				}
				else if (key->scancode == sf::Keyboard::Scan::N) {
					stepOnce = true;
					std::cout << "Step forward\n";
				}
				else if (key->scancode == sf::Keyboard::Scan::I) {
					game.toggle_icon_mode();
					std::cout << "Toggled icon mode\n";
				}
				else if (key->scancode == sf::Keyboard::Scan::L) {
					darkMode = !darkMode;
					std::cout << (darkMode ? "Dark Mode\n" : "Light Mode\n");
				}
				else if (key->scancode == sf::Keyboard::Scan::M) {
					isMuted = !isMuted;
					ma_sound_set_volume(&music, isMuted ? 0.0f : 1.0f);
					std::cout << (isMuted ? "Muted\n" : "Unmuted\n");
				}




			}



		}
		//cell textures:)
		game.set_cell_texture(&cellTexture);// Falcon
		game.set_dead_cell_texture(&deadTexture);// Black hole
		game.set_alt_cell_texture(&tieTexture);     // TIE Fighter

		window.clear();
			sf::RectangleShape headerBar;
			headerBar.setSize(sf::Vector2f(window.getSize().x, 80));
			headerBar.setFillColor(sf::Color(20, 20, 20,70));
		window.draw(darkMode ? darkSprite : lightSprite);
		window.draw(headerBar);

		window.draw(title);
		game.draw(paused);
		window.draw(instructions);
		if (darkMode)
		{
			instructions.setFillColor(sf::Color(180, 180, 180));
		}
		else if (!darkMode)
		{
			instructions.setFillColor(sf::Color(255, 255, 255));
		}
		if (paused) {
			sf::Text pausedText(font, "PAUSED", 48);
			if (!darkMode)
			{
				pausedText.setFillColor(sf::Color(30, 30, 30, 190));
			}
			else
			{
				pausedText.setFillColor(sf::Color(255, 255, 255, 190));
			}
			sf::FloatRect bounds = pausedText.getLocalBounds();
			pausedText.setOrigin(bounds.position + bounds.size / 2.f);
			pausedText.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });


			if (paused && !stepOnce) {
				window.draw(pausedText);
			}

		}
		if (!paused || stepOnce) {
			game.next_generation();
			stepOnce = false;
		}


		window.display();

	}
	
	ma_sound_uninit(&music);
	ma_engine_uninit(&engine);


	return 0;
}
