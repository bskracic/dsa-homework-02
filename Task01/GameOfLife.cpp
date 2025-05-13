#include "GameOfLife.h"
#include <SFML/System.hpp>
#include <iostream>

GameOfLife::GameOfLife(sf::RenderWindow* window)
{
    this->window = window;
    sf::RectangleShape r({ 20.f,20.f });

    for (int i = 0; i < rows; i++) {
        vector<sf::RectangleShape> row;
        for (int j = 0; j < columns; j++) {
            if ((1 + rand() % 100) <= 25) r.setFillColor(sf::Color(45, 85, 166));
            else r.setFillColor(sf::Color::Transparent);
            r.setPosition({ 20.f * j, 20.f * i });
            row.push_back(r);
        }
        // initially both generation are the same
        currentGeneration.push_back(row);
        nextGeneration.push_back(row);
    }
}

void GameOfLife::setGeneration()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++) {
            // checking if an individual cell is taken
            if (cellTaken(i, j)) {
                // and the number of its neighbors
                if (getNeighbors(i, j) == 2 or getNeighbors(i, j) == 3) {
                    sf::RectangleShape r({ 20.f,20.f });
                    r.setFillColor(sf::Color(45, 85, 166));
                    r.setPosition({ 20.f * j, 20.f * i });
                    nextGeneration[i][j] = r;
                }
                else {
                    sf::RectangleShape r({ 20.f,20.f });
                    r.setFillColor(sf::Color::Transparent);
                    r.setPosition({ 20.f * j, 20.f * i });
                    nextGeneration[i][j] = r;
                }
            }
            // if a cell is dead
            else {
                // and has 3 neighbors
                if (getNeighbors(i, j) == 3) {
                    sf::RectangleShape r({ 20.f,20.f });
                    r.setFillColor(sf::Color(18, 12, 122));
                    r.setPosition({ 20.f * j, 20.f * i });
                    nextGeneration[i][j] = r;
                }
                // or not
                else {
                    sf::RectangleShape r({ 20.f,20.f });
                    r.setFillColor(sf::Color::Transparent);
                    r.setPosition({ 20.f * j, 20.f * i });
                    nextGeneration[i][j] = r;
                }
            }
        }
    }
    // changing new current generation
    currentGeneration = nextGeneration;
}

void GameOfLife::draw()
{
    sf::Clock timer;

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window->close();
        }

        // update generation every 2 seconds
        if (timer.getElapsedTime().asSeconds() >= 2.f) {
            setGeneration();
            timer.restart();
        }

        window->clear(sf::Color(2, 7, 36));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                window->draw(currentGeneration[i][j]);
            }
        }
        window->display();
    }
}

bool GameOfLife::cellTaken(int i, int j)
{
    if (currentGeneration[i][j].getFillColor() == sf::Color::Transparent) return false;
    return true;
}

int GameOfLife::getNeighbors(int i, int j)
{
    // checking all the possible variations of boundaries
    int neighbors = 0;
    if (i == 0 and j == 0) {
        if (cellTaken(i, j + 1)) neighbors++;
        if (cellTaken(i + 1, j)) neighbors++;
        if (cellTaken(i + 1, j + 1)) neighbors++;
    }
    else if (i == 0 and j == columns - 1) {
        if (cellTaken(i, j - 1)) neighbors++;
        if (cellTaken(i + 1, j - 1)) neighbors++;
        if (cellTaken(i + 1, j)) neighbors++;
    }
    else if (i == rows - 1 and j == columns - 1) {
        if (cellTaken(i - 1, j - 1)) neighbors++;
        if (cellTaken(i, j - 1)) neighbors++;
        if (cellTaken(i - 1, j)) neighbors++;
    }
    else if (i == rows - 1 and j == 0) {
        if (cellTaken(i - 1, j)) neighbors++;
        if (cellTaken(i - 1, j + 1)) neighbors++;
        if (cellTaken(i, j + 1)) neighbors++;
    }
    else if (i == 0) {
        if (cellTaken(i, j - 1)) neighbors++;
        if (cellTaken(i, j + 1)) neighbors++;
        if (cellTaken(i + 1, j)) neighbors++;
        if (cellTaken(i + 1, j + 1)) neighbors++;
        if (cellTaken(i + 1, j - 1)) neighbors++;
    }
    else if (j == 0) {
        if (cellTaken(i - 1, j)) neighbors++;
        if (cellTaken(i - 1, j + 1)) neighbors++;
        if (cellTaken(i, j + 1)) neighbors++;
        if (cellTaken(i + 1, j)) neighbors++;
        if (cellTaken(i + 1, j + 1)) neighbors++;
    }
    else if (i == rows - 1) {
        if (cellTaken(i, j - 1)) neighbors++;
        if (cellTaken(i - 1, j - 1)) neighbors++;
        if (cellTaken(i - 1, j)) neighbors++;
        if (cellTaken(i - 1, j + 1)) neighbors++;
        if (cellTaken(i, j + 1)) neighbors++;
    }
    else if (j == columns - 1) {
        if (cellTaken(i, j - 1)) neighbors++;
        if (cellTaken(i - 1, j - 1)) neighbors++;
        if (cellTaken(i - 1, j)) neighbors++;
        if (cellTaken(i + 1, j - 1)) neighbors++;
        if (cellTaken(i + 1, j)) neighbors++;
    }
    else{
        if (cellTaken(i - 1, j - 1)) neighbors++;
        if (cellTaken(i - 1, j)) neighbors++;
        if (cellTaken(i - 1, j + 1)) neighbors++;
        if (cellTaken(i, j - 1)) neighbors++;
        if (cellTaken(i, j + 1)) neighbors++;
        if (cellTaken(i + 1, j - 1)) neighbors++;
        if (cellTaken(i + 1, j)) neighbors++;
        if (cellTaken(i + 1, j + 1)) neighbors++;
    }
    return neighbors;
}
