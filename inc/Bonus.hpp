#pragma once
#include <SFML/Graphics.hpp>

enum class BonusType {
    Coin,
    Trap
};

class Bonus {
public:
    Bonus(float x, float y, BonusType type);
    void update(float dt, float speed);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;
    BonusType getType() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    BonusType type;
};