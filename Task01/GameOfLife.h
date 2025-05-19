#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameOfLife {
public:
    GameOfLife(int rows, int cols, float cellSize);

    void randomInitialize();
    void update();
    void draw(sf::RenderWindow& window) const;
    const std::vector<std::vector<bool>>& getGrid() const { return grid; }

private:
    int rows;
    int cols;
    float cellSize;

    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> nextGrid;



    int countLiveNeighbors(int r, int c) const;
};
