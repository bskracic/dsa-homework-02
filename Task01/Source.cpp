#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include "GameOfLife.h"
using namespace std;

int main() {

    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "Game of Life");

    GameOfLife game(&window);
    game.draw();

}