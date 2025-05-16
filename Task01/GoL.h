#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class cellState {
    Dead,
    Alive,
    Dying,
    Birthing,
    Sacrificing
};

struct cell {
    cellState state;
    sf::Sprite sprite;
    float animTimer;
    bool isAnim;

    cell(cellState init, const sf::Texture& tex);

    void setPos(float x, float y, float cell_size);
    void update(float dt,
        const sf::Texture& texAlive,
        const sf::Texture& texDead,
        const sf::Texture& texMito,
        const sf::Texture& texApop,
        const sf::Texture& texMito2,
        const sf::Texture& texApop2,
        const sf::Texture& texSac1,
        const sf::Texture& texSac2);
    void ded();
    void birth();
    void sacrifice();
    void commitState();
    bool isAlive() const;
    bool isLogicAlive() const;
    bool shouldDraw() const;
};

class gameOfLife : public sf::Drawable {
public:
    gameOfLife(float cell_size);
    void update_state(float dt);
    int get_Msize();
    void prepare_next_gen();
    void commit_next_gen();

private:
    static const int MATRIX_SIZE = 10;
    float cell_size;
    std::vector<std::vector<bool>> nextAlive;

    std::vector<std::vector<cell>> matrix;

    sf::Texture texAlive;
    sf::Texture texAliveAlt;
    sf::Texture texDead;
    sf::Texture texMito;
    sf::Texture texApop;
    sf::Texture texMito2;
    sf::Texture texApop2;
    sf::Texture texSac1;
    sf::Texture texSac2;

    float passiveAnimTimer = 0.f;
    bool useAlt = false;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    int countAliveNeighbors(int x, int y) const;
};