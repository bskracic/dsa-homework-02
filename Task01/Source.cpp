#include <SFML/Graphics.hpp>
#include "GameOfLife.h"
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cmath> // For smooth color transitions

int main()
{
    const int ROWS = 80;
    const int COLS = 120;
    const float CELL_SIZE = 9.f;
    int delay_ms = 2000; // Default 2000ms delay
    bool paused = false;
    int generation = 0;
    float hue_offset = 0.0f; // For color animation

    // Calculate dimensions as integers first
    const signed width = COLS * static_cast<unsigned>(CELL_SIZE);
    const signed height = ROWS * static_cast<unsigned>(CELL_SIZE) + 30;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Game of Life");



    window.setVerticalSyncEnabled(false);
    GameOfLife game(ROWS, COLS, CELL_SIZE);

    // Font and text initialization
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text generationText(font, "", 20);
    generationText.setFillColor(sf::Color::Magenta);
    generationText.setPosition(sf::Vector2f(10.f, static_cast<float>(ROWS * CELL_SIZE)));

    sf::Clock frameClock;
    sf::Clock delayClock;
    sf::Clock colorClock; // For smooth color transitions
    int frameCount = 0;
    float currentFPS = 0.0f;

    // Store cell ages for smooth transitions
    std::vector<std::vector<float>> cellAges(ROWS, std::vector<float>(COLS, 0.0f));

    while (window.isOpen()) {
        float deltaTime = colorClock.restart().asSeconds();
        hue_offset += deltaTime * 0.1f; // Slowly cycle colors

        // Calculate FPS
        frameCount++;
        if (frameClock.getElapsedTime().asSeconds() >= 0.1f) {
            currentFPS = frameCount / frameClock.getElapsedTime().asSeconds();
            frameCount = 0;
            frameClock.restart();
        }

        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->scancode == sf::Keyboard::Scancode::Space) {
                    paused = !paused;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scancode::Down) {
                    delay_ms = std::max(0, delay_ms - 100);
                }
                else if (keyEvent->scancode == sf::Keyboard::Scancode::Up) {
                    delay_ms = std::min(5000, delay_ms + 100);
                }
            }
        }

        window.clear(sf::Color(20, 20, 40)); // Dark blue background

        // Update game state
        if (!paused && delayClock.getElapsedTime().asMilliseconds() >= delay_ms) {
            game.update();
            generation++;
            delayClock.restart();

            // Update cell ages for smooth transitions
            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    if (game.getGrid()[r][c]) {
                        cellAges[r][c] += deltaTime;
                    }
                    else {
                        cellAges[r][c] = 0.0f;
                    }
                }
            }
        }

        // Draw cells with smooth color transitions
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
        const auto& grid = game.getGrid();

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c]) {
                    // Color based on position and age
                    float hue = fmod(hue_offset + cellAges[r][c] * 0.5f + (r + c) * 0.001f, 1.0f);
                    float saturation = 0.8f + 0.2f * sin(cellAges[r][c] * 2.0f);
                    float value = 0.9f + 0.1f * sin(cellAges[r][c] * 3.0f);

                    // Convert HSV to RGB
                    float chroma = value * saturation;
                    float huePrime = hue * 6.0f;
                    float x = chroma * (1 - abs(fmod(huePrime, 2) - 1));

                    sf::Color cellColor;
                    if (huePrime < 1) cellColor = sf::Color(chroma * 255, x * 255, 0);
                    else if (huePrime < 2) cellColor = sf::Color(x * 255, chroma * 255, 0);
                    else if (huePrime < 3) cellColor = sf::Color(0, chroma * 255, x * 255);
                    else if (huePrime < 4) cellColor = sf::Color(0, x * 255, chroma * 255);
                    else if (huePrime < 5) cellColor = sf::Color(x * 255, 0, chroma * 255);
                    else cellColor = sf::Color(chroma * 255, 0, x * 255);

                    cell.setFillColor(cellColor);
                    cell.setPosition(sf::Vector2f(
                        static_cast<float>(c) * CELL_SIZE,
                        static_cast<float>(r) * CELL_SIZE
                    ));
                    window.draw(cell);
                }
            }
        }

        // Update and draw generation text
        std::stringstream ss;
        ss << "Generation: " << generation
            << "   Delay: " << delay_ms << "ms"
            << "   FPS: " << static_cast<int>(currentFPS)
            << "   [SPACE: Pause/Resume]"
            << "   [Arrows UP/DOWN: Change Speed]";
        generationText.setString(ss.str());
        window.draw(generationText);

        window.display();
    }

    return 0;
}