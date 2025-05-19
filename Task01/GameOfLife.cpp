#include "GameOfLife.h"
#include <cstdlib>
#include <ctime>

GameOfLife::GameOfLife(int rows, int cols, float size)
    : rows(rows), cols(cols), cellSize(size),
    grid(rows, std::vector<bool>(cols, false)),
    nextGrid(rows, std::vector<bool>(cols, false))
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    randomInitialize();
}

void GameOfLife::randomInitialize() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            grid[r][c] = (std::rand() % 100) < 25; // 25% alive
}

int GameOfLife::countLiveNeighbors(int r, int c) const {
    static const int directions[8][2] = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    int count = 0;
    for (const auto& dir : directions) {
        int newRow = r + dir[0];
        int newCol = c + dir[1];
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
            if (grid[newRow][newCol])
                ++count;
    }
    return count;
}

void GameOfLife::update() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int neighbors = countLiveNeighbors(r, c);
            if (grid[r][c])
                nextGrid[r][c] = (neighbors == 2 || neighbors == 3);
            else
                nextGrid[r][c] = (neighbors == 3);
        }
    }
    grid.swap(nextGrid);
}

void GameOfLife::draw(sf::RenderWindow& window) const {
    sf::RectangleShape cellShape({ cellSize - 1, cellSize - 1 });
    cellShape.setFillColor(sf::Color::Yellow);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c]) {
                cellShape.setPosition(sf::Vector2f(c * cellSize, r * cellSize));
                window.draw(cellShape);
            }
        }
    }
}
