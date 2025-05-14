#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <SFML/Graphics.hpp>  // added
#include <iostream>
#include <string>
#include <fstream>


class game_of_life {
private:
    unsigned int COLS = 0;
    unsigned int ROWS = 0;
    float cellSize = 20.f;

    std::vector<std::vector<bool>> _generation;
    std::vector<std::vector<bool>> _next_generation;

    sf::RenderWindow* window = nullptr; 

    bool random_value();
    bool cell_taken(int i, int j);
    float offsetX = 0.f;
    float offsetY = 0.f;


public:
    game_of_life();
    void set_window(sf::RenderWindow* window); 
    void initialize_grid(sf::Vector2u windowSize, float preferredSize = 20.f);
    void next_generation();
    void draw(); 
};

#endif
