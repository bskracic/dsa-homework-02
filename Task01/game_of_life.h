#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <SFML/Graphics.hpp>  
#include <iostream>
#include <string>
#include <fstream>


class game_of_life {
private:
    static const unsigned int COLS = 80;
    static const unsigned int ROWS = 43;
    float cellSize = 20.f;

    bool _generation[ROWS][COLS];
    bool _next_generation[ROWS][COLS];

    sf::RenderWindow* window = nullptr; 

    bool random_value();
    bool cell_taken(int i, int j);


public:
    game_of_life();
    void set_window(sf::RenderWindow* window); 
    void next_generation();
    void draw(); 

    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;
    void reset();

};

#endif
