#include "Bonus.hpp"

Bonus::Bonus(float x, float y, BonusType type) : type(type) {
    if (type == BonusType::Coin)
        texture.loadFromFile("assets/bonus.png");
    else
        texture.loadFromFile("assets/trap.png");
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Bonus::update(float dt, float speed) {
    sprite.move(-speed * dt, 0);
}

void Bonus::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bonus::isOffScreen() const {
    return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

sf::FloatRect Bonus::getBounds() const {
    return sprite.getGlobalBounds();
}

BonusType Bonus::getType() const {
    return type;
}