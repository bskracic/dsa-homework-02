#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <SFML/Graphics.hpp>  
#include <iostream>
#include <string>
#include <fstream>


class game_of_life {
private:
    //static const unsigned int COLS = 80;
    //static const unsigned int ROWS = 43;
    //float cellSize = 20.f;
    static const unsigned int COLS =53;
    static const unsigned int ROWS = 28;
    float cellSize = 30.f;

    bool _generation[ROWS][COLS];
    bool _next_generation[ROWS][COLS];

    sf::RenderWindow* window = nullptr; 

    bool random_value();
    bool cell_taken(int i, int j);
    sf::Texture* cellTexture = nullptr;
    sf::Texture* deadCellTexture = nullptr;


public:
    game_of_life();
    void set_window(sf::RenderWindow* window); 
    void next_generation();
    void draw(bool paused = false);
    void set_cell_texture(sf::Texture* texture);
    void set_dead_cell_texture(sf::Texture* texture);

    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;
    void reset();

    bool useIcons = false;
    void toggle_icon_mode();


};

#endif
