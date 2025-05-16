//SIUUU

#include "GoL.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>      
#include <utility>    
#include <algorithm>  
#include <random>      

//it is official that Conway should've been shot with paintball guns

cell::cell(cellState init, const sf::Texture& tex)
    : state(init), sprite(tex), animTimer(0.f), isAnim(false) {}

void cell::setPos(float x, float y, float cell_size) {
    sprite.setPosition(sf::Vector2f{ x, y });
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f{ cell_size / bounds.size.x, cell_size / bounds.size.y });
}

void cell::update(float dt,
    const sf::Texture& texAlive, const sf::Texture& texDead,
    const sf::Texture& texMito, const sf::Texture& texApop,
    const sf::Texture& texMito2, const sf::Texture& texApop2,
    const sf::Texture& texSac1, const sf::Texture& texSac2) {
    if (!isAnim) return;

    animTimer += dt;

    switch (state) {
    case cellState::Dying:
        if (animTimer < 0.5f)
            sprite.setTexture(texApop);
        else if (animTimer < 1.0f)
            sprite.setTexture(texApop2);
        else {
            sprite.setTexture(texDead);
            state = cellState::Dead;
            isAnim = false;
        }
        break;
    case cellState::Birthing:
        if (animTimer < 0.5f)
            sprite.setTexture(texMito);
        else if (animTimer < 1.0f)
            sprite.setTexture(texMito2);
        else {
            sprite.setTexture(texAlive);
            state = cellState::Alive;
            isAnim = false;
        }
        break;
    case cellState::Sacrificing:
        if (animTimer < 0.5f)
            sprite.setTexture(texSac1);
        else if (animTimer < 1.0f)
            sprite.setTexture(texSac2);
        else {
            sprite.setTexture(texDead);
            state = cellState::Dead;
            isAnim = false;
        }
        break;
    default:
        break;
    }
}

void cell::ded() {
    state = cellState::Dying;
    animTimer = 0.f;
    isAnim = true;
}

void cell::birth() {
    state = cellState::Birthing;
    animTimer = 0.f;
    isAnim = true;
}

void cell::sacrifice() {
    state = cellState::Sacrificing;
    animTimer = 0.f;
    isAnim = true;
}

void cell::commitState() {
    if (state == cellState::Birthing) state = cellState::Alive;
    if (state == cellState::Dying) state = cellState::Dead;
    isAnim = false;
}

bool cell::isAlive() const {
    return state == cellState::Alive || state == cellState::Birthing;
}

bool cell::isLogicAlive() const {
    return state == cellState::Alive;
}

bool cell::shouldDraw() const {
    return state != cellState::Dead;
}

// abandon all hope, ye who enter here

gameOfLife::gameOfLife(float cs, int ms) : cell_size(cs) {
    std::srand((std::time(nullptr)));

    if (!texAlive.loadFromFile("sprites/s_cell_nobg.png"))
        std::cerr << "Failed to load alive texture\n";
    if (!texAliveAlt.loadFromFile("sprites/s_cell_S_nobg.png"))
        std::cerr << "Failed to load alt alive texture\n";
    if (!texDead.loadFromFile("sprites/s_cell_ded_nobg.png"))
        std::cerr << "Failed to load dead texture\n";
    if (!texApop.loadFromFile("sprites/s_apoptosis_nobg.png"))
        std::cerr << "Failed to load apoptosis texture\n";
    if (!texMito.loadFromFile("sprites/s_mitosis_nobg.png"))
        std::cerr << "Failed to load mitosis texture\n";
    if (!texMito2.loadFromFile("sprites/s_mitosis_2_nobg.png"))
        std::cerr << "Failed to load mitosis texture\n";
    if (!texApop2.loadFromFile("sprites/s_cell_apoptosis_2_nobg.png"))
        std::cerr << "Failed to load mitosis texture\n";
    if (!texSac1.loadFromFile("sprites/s_sacrifice_1.png"))
        std::cerr << "Failed to load sacrifice texture\n";
    if (!texSac2.loadFromFile("sprites/s_sacrifice_2.png"))
        std::cerr << "Failed to load sacrifice texture\n";

    this->matrix_size = ms;
    nextAlive.resize(matrix_size, std::vector<bool>(matrix_size, false));

    for (int y = 0; y < ms; ++y) {
        std::vector<cell> row;
        for (int x = 0; x < ms; ++x) {
            bool isAlive = (std::rand() % 100) < 25;
            cellState state = isAlive ? cellState::Alive : cellState::Dead;
            const sf::Texture& tex = isAlive ? texAlive : texDead;

            row.emplace_back(state, tex);
            row.back().setPos(x * cell_size, y * cell_size, cell_size);
        }
        matrix.push_back(std::move(row));
    }
}

void gameOfLife::update_state(float dt) {
    for (auto& row : matrix)
        for (auto& c : row)
            c.update(dt, texAlive, texDead, texMito, texApop, texMito2, texApop2, texSac1, texSac2);
    passiveAnimTimer += dt;
    if (passiveAnimTimer >= 0.5f) {
        passiveAnimTimer = 0.f;
        useAlt = !useAlt;

        for (auto& row : matrix) {
            for (auto& c : row) {
                if (c.state == cellState::Alive && !c.isAnim) {
                    c.sprite.setTexture(useAlt ? texAliveAlt : texAlive); // curse me for being fucking retarded enough to do this shite
                }
            }
        }
    }
}

void gameOfLife::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& row : matrix)
        for (const auto& c : row)
            if (c.shouldDraw())
                target.draw(c.sprite, states);
}

int gameOfLife::countAliveNeighbors(int x, int y) const {
    static const int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    static const int dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < matrix_size && ny >= 0 && ny < matrix_size) {
            if (matrix[ny][nx].isAlive()) {  // was matrix[nx][ny]
                count++;
            }
        }
    }
    return count;
}

int gameOfLife::get_Msize()
{
    return matrix_size;
}

//the rothschilds have paid this function not to work
void gameOfLife::prepare_next_gen() {
    static std::mt19937 rng(std::random_device{}());

    // print matrix :: for debug only
    /*std::cout << "\nGrid State:\n";
    for (int y = 0; y < MATRIX_SIZE; ++y) {
        for (int x = 0; x < MATRIX_SIZE; ++x) {
            std::cout << (matrix[y][x].isLogicAlive() ? "1 " : "0 ");
        }
        std::cout << "\n";
    }*/

    // next state
    for (int y = 0; y < matrix_size; ++y) {
        for (int x = 0; x < matrix_size; ++x) {
            int neighbors = countAliveNeighbors(x, y);
            bool alive = matrix[y][x].isLogicAlive();

            nextAlive[y][x] =
                (alive && (neighbors == 2 || neighbors == 3)) ||
                (!alive && neighbors == 3);
        }
    }
    static const int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    static const int dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    // animate
    for (int y = 0; y < matrix_size; ++y) {
        for (int x = 0; x < matrix_size; ++x) {
            bool currentlyAlive = matrix[y][x].isLogicAlive();
            bool willBeAlive = nextAlive[y][x];

            if (currentlyAlive && !willBeAlive) {
                bool causesBirth = false;
                
                for (int i = 0; i < 8; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < matrix_size && ny >= 0 && ny < matrix_size) {
                        if (!matrix[ny][nx].isLogicAlive() && nextAlive[ny][nx]) {
                            causesBirth = true;
                            break;
                        }
                    }
                }
                if (causesBirth)
                    matrix[y][x].sacrifice();
                else
                    matrix[y][x].ded();
            }
            else if (!currentlyAlive && willBeAlive) {
                // if cell born -> neighbour births it
                std::array<std::pair<int, int>, 8> directions = { {
                    {-1, -1}, {-1, 0}, {-1, 1},
                    { 0,  1}, { 1,  1}, { 1, 0},
                    { 1, -1}, { 0, -1}
                } };
                std::shuffle(directions.begin(), directions.end(), rng);

                for (auto [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < matrix_size && ny >= 0 && ny < matrix_size &&
                        matrix[ny][nx].isLogicAlive()) {
                        matrix[ny][nx].birth();  // show mitosis on the parent
                        break;
                    }
                }
            }
        }
    }
}

void gameOfLife::commit_next_gen() {
    for (int y = 0; y < matrix_size; ++y) {
        for (int x = 0; x < matrix_size; ++x) {
            cell& c = matrix[y][x];
            c.commitState();

            if (c.isAnim) //don't break animation
                continue;

            // apply state
            if (nextAlive[y][x]) {
                c.state = cellState::Alive;
                c.sprite.setTexture(useAlt ? texAliveAlt : texAlive);
            }
            else {
                c.state = cellState::Dead;
                c.sprite.setTexture(texDead);
            }
        }
    }
}