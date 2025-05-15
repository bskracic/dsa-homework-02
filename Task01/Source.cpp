#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <optional>
#include <algorithm>

const int MAX_CELLS = 100000;
const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;
const double UPDATE_INTERVAL = 2.0;

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int gridInitialW, gridInitialH;
    std::cout << "Enter the initial size of the grid width and height (max total cells " << MAX_CELLS << "): ";
    std::cin >> gridInitialW >> gridInitialH;

    if (gridInitialW <= 0 || gridInitialH <= 0 || gridInitialW * gridInitialH > MAX_CELLS) {
        std::cerr << "Error: grid width and height must be > 0 and total cells <= " << MAX_CELLS << ".\n";
        return 1;
    }

    std::vector<bool> grid(gridInitialW * gridInitialH);

    for (int i = 0; i < gridInitialW * gridInitialH; ++i) {
        grid[i] = (std::rand() % 4) == 0;
    }

    sf::RenderWindow window(sf::VideoMode({ WINDOW_W, WINDOW_H }), "Game of Life - Static");

    float scaleX = static_cast<float>(WINDOW_W) / gridInitialW;
    float scaleY = static_cast<float>(WINDOW_H) / gridInitialH;
    float scale = std::min(scaleX, scaleY);

    int cellSize = static_cast<int>(scale);

    bool drawScaled = (cellSize > 0);
    if (!drawScaled) {
        cellSize = 1;
    }
    else {
        std::cout << "Cell size: " << cellSize << "x" << cellSize << " pixels.\n";
    }

    sf::RectangleShape cellShape;
    cellShape.setFillColor(sf::Color::White);
    cellShape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        for (int y = 0; y < gridInitialH; ++y) {
            for (int x = 0; x < gridInitialW; ++x) {
                int index = y * gridInitialW + x;

                if (grid[index]) {
                    int posX = x * cellSize;
                    int posY = y * cellSize;

                    if (posX < WINDOW_W && posY < WINDOW_H) {
                        cellShape.setPosition(sf::Vector2f(static_cast<float>(posX), static_cast<float>(posY)));
                        window.draw(cellShape);
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}