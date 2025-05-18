#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <SFML/Graphics.hpp>  
#include <iostream>
#include <string>
#include <fstream>


class game_of_life {
private:

  /*  static const unsigned int COLS = 26;
    static const unsigned int ROWS = 14;
    float cellSize = 60.f;


    bool _generation[ROWS][COLS];
    bool _next_generation[ROWS][COLS];*/

    static const unsigned int COLOR_MODE_COLS = 104;
    static const unsigned int COLOR_MODE_ROWS = 56;


    static const unsigned int ICON_MODE_COLS = 26;
    static const unsigned int ICON_MODE_ROWS = 14;

    static const unsigned int MAX_COLS = COLOR_MODE_COLS;
    static const unsigned int MAX_ROWS = COLOR_MODE_ROWS;

    float cellSize = 60.f;

    unsigned int activeCols = ICON_MODE_COLS;
    unsigned int activeRows = ICON_MODE_ROWS;

    bool _generation[MAX_ROWS][MAX_COLS];
    bool _next_generation[MAX_ROWS][MAX_COLS];


    sf::RenderWindow* window = nullptr; 

    bool random_value();
    bool cell_taken(int i, int j);
    sf::Texture* cellTexture = nullptr;
    sf::Texture* deadCellTexture = nullptr;
    sf::Texture* altCellTexture = nullptr;

public:
    game_of_life();
    void set_window(sf::RenderWindow* window); 
    void next_generation();
    void draw(bool paused = false);
    void set_cell_texture(sf::Texture* texture);
    void set_dead_cell_texture(sf::Texture* texture);
    void set_alt_cell_texture(sf::Texture* texture);

    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;
    void reset();

    bool useIcons = true;
    void toggle_icon_mode();

    bool darkMode = true;

};

#endif
