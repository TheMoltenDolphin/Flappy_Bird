#include "Bonus.hpp"

Bonus::Bonus(float x, float y, BonusType type) : type(type) {
    static sf::Texture coinTexture;
    static sf::Texture trapTexture;
    static bool coinLoaded = false;
    static bool trapLoaded = false;

    if (!coinLoaded) {
        coinLoaded = coinTexture.loadFromFile("assets/bonus.png");
    }
    if (!trapLoaded) {
        trapLoaded = trapTexture.loadFromFile("assets/trap.png");
    }

    if (type == BonusType::Coin) {
        texture = coinTexture;
    } else {
        texture = trapTexture;
    }

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