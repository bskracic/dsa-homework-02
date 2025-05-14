#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>

const int MAX_CELLS = 100000;
const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;
const double UPDATE_INTERVAL = 2.0; 

int main() {
    std::srand((std::time(nullptr)));

    int gridInitialW, gridInitialH;

    std::cout << "Enter the initial size of the grid width and height (max total cells "
        << MAX_CELLS << "): ";
    std::cin >> gridInitialW >> gridInitialH;
    if (gridInitialW <= 0 || gridInitialH <= 0 || gridInitialW * gridInitialH > MAX_CELLS) {
        std::cerr << "Error:grid height or width must be >0 and ≤"
            << MAX_CELLS << "\n";
        return 1;
    }

    std::vector<bool> grid(gridInitialW * gridInitialH);

    for (int i = 0; i < gridInitialW * gridInitialH; ++i) {
        grid[i] = (std::rand() % (4 - 1) + 1) == 1;
    }

    //error
    //sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Conway's Game of Life (SFML)");
    //window.setFramerateLimit(60);

    //TODO: start from initial grid of colored alide pixels and black dead pixels, dynamically zoom out to preserve scale of the game of life even with 100 000 cells.


    return 0;
}