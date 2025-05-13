#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <SFML/Graphics.hpp>  // added
#include <iostream>
#include <string>
#include <fstream>

class game_of_life {
private:
    static const unsigned int COLS = 40;
    static const unsigned int ROWS = 30;

    bool _generation[ROWS][COLS];
    bool _next_generation[ROWS][COLS];

    sf::RenderWindow* window = nullptr; // pointer to window
    float cellSize = 20.f; // pixels per cell

    bool random_value();
    bool cell_taken(int i, int j);

public:
    game_of_life();
    void set_window(sf::RenderWindow* window); // assign the window
    void next_generation();
    void draw(); // will now draw rectangles
};

#endif
