#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <optional>
#include <algorithm>
#include <cstdlib>
#include <cctype>

const int MAX_CELLS = 99999;
const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;

int countLiveNeighbors(int x, int y, int gridW, int gridH, const std::vector<bool>& currentGrid) {
    int liveNeighbors = 0;
    for (int dx = std::max(-1, -x); dx <= std::min(1, gridW - 1 - x); ++dx) {
        for (int dy = std::max(-1, -y); dy <= std::min(1, gridH - 1 - y); ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            int neighborX = x + dx;
            int neighborY = y + dy;

            int neighborIndex = neighborY * gridW + neighborX;

            if (currentGrid[neighborIndex]) {
                liveNeighbors++;
            }
        }
    }
    return liveNeighbors;
}
// Choose colors avoding bleak colors or black
sf::Color generateBrightRandomColor() {
    int r, g, b;
    switch (std::rand() % 3) {
    case 0:
        r = 200 + std::rand() % 56;
        g = 50 + std::rand() % 206;
        b = 50 + std::rand() % 206;
        break;
    case 1:
        r = 50 + std::rand() % 206;
        g = 200 + std::rand() % 56;
        b = 50 + std::rand() % 206;
        break;
    case 2:
        r = 50 + std::rand() % 206;
        g = 50 + std::rand() % 206;
        b = 200 + std::rand() % 56;
        break;
    }
    return sf::Color(r, g, b);
}

int main()
{
    std::srand(std::time(nullptr));

    int gridInitialW, gridInitialH;
    std::cout << "Enter the initial size of the grid width and height (max total cells " << MAX_CELLS << "): ";
    std::cin >> gridInitialW >> gridInitialH;

    if (gridInitialW <= 0 || gridInitialH <= 0 || gridInitialW * gridInitialH > MAX_CELLS) {
        std::cerr << "Error: grid width and height must be > 0 and total cells <= " << MAX_CELLS << ".\n";
        return 1;
    }

    char shizoModeChoice;
    std::cout << "Do you want to enter Shizo Mode? (Y/N): ";
    std::cin >> shizoModeChoice;

    bool useShizoMode = (std::tolower(shizoModeChoice) == 'y');

    // sf::Music shizoSound;

    if (useShizoMode) {
        std::cout << "Shizo Mode enabled! Colors will flash rapidly.\n";

        // if (!shizoSound.openFromFile("shizo_mode_music.wav")) {
        //    std::cerr << "Failed to load soundtrack!\n";
        //    return -1;
        // }

       // shizoSound.setLooping(true);
       // shizoSound.play();
    }
    else {
        std::cout << "Using default white color for alive cells.\n";
    }


    int totalCells = gridInitialW * gridInitialH;
    std::vector<bool> grid(totalCells);
    std::vector<bool> nextGrid(totalCells);
    std::vector<sf::Color> colorGrid(totalCells);

    for (int i = 0; i < totalCells; ++i) {
        grid[i] = (std::rand() % 4) == 0;
        if (grid[i]) {
            if (useShizoMode) {
                colorGrid[i] = generateBrightRandomColor();
            }
            else {
                colorGrid[i] = sf::Color::White;
            }
        }
        else {
            colorGrid[i] = sf::Color::Black;
        }
    }

    sf::RenderWindow window(sf::VideoMode({ WINDOW_W, WINDOW_H }), "Game of Life");

    window.setFramerateLimit(60);

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
    cellShape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            // TODO: Detect mouse click. If cell dead - convert to alive, if alive - kill it. Convert coordinates of the click, correctly apply color
        }

        for (int y = 0; y < gridInitialH; ++y) {
            for (int x = 0; x < gridInitialW; ++x) {
                int index = y * gridInitialW + x;

                int liveNeighbors = countLiveNeighbors(x, y, gridInitialW, gridInitialH, grid);
                bool currentState = grid[index];
                bool nextState = currentState;

                if (currentState) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        nextState = false;
                    }
                }
                else {
                    if (liveNeighbors == 3) {
                        nextState = true;
                        if (useShizoMode) {
                            colorGrid[index] = generateBrightRandomColor();
                        }
                        else {
                            colorGrid[index] = sf::Color::White;
                        }
                    }
                }
                nextGrid[index] = nextState;
            }
        }

        grid.swap(nextGrid);


        // In Shizo Mode, change colors of alive cells every frame
        if (useShizoMode) {
            for (int i = 0; i < totalCells; ++i) {
                if (grid[i]) {
                    colorGrid[i] = generateBrightRandomColor();
                }
            }
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
                        cellShape.setFillColor(colorGrid[index]);
                        window.draw(cellShape);
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}