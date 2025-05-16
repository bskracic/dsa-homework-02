#include <SFML/Graphics.hpp>
#include "GoL.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

int main() {
    unsigned int window_size = 1500;
    int matrix_size = 10;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u{ window_size, window_size }), "Game of Life");
    float cell_size = window_size / matrix_size;
    gameOfLife gol(cell_size, matrix_size); //SIUUU

    bool prepared = false;
    bool committed = false;
    bool first = true;

    sf::Clock frameClock;
    sf::Clock updateClock;

    while (window.isOpen()) {
        float dt = updateClock.getElapsedTime().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (first && dt < 2.0f) {
            // wanna see the 1st one
        }
        else {
            if (first) {
                first = false;
                updateClock.restart();
                dt = 0.f;
            }

            if (!prepared && dt >= 0.01f) {
                gol.prepare_next_gen();
                prepared = true;
            }

            if (!committed && dt >= 1.0f) {
                gol.commit_next_gen();
                committed = true;
                updateClock.restart();
            }

            if (dt >= 2.0f) {
                updateClock.restart();
                prepared = false;
                committed = false;
            }
        }

        // animate
        float dx = frameClock.restart().asSeconds();
        gol.update_state(dx);


        window.clear(sf::Color(212, 183, 201));
        window.draw(gol);
        window.display();
    }
    return 0;
}