#include "Bird.hpp"

Bird::Bird() : velocity(0.f) {
    texture.loadFromFile("assets/bird.png");
    sprite.setTexture(texture);
    sprite.setPosition(300, 400);
}

void Bird::update(float dt) {
    velocity += gravity * dt;
    sprite.move(0, velocity * dt);
}

void Bird::flap() {
    velocity = flapStrength;
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}

void Bird::reset() {
    sprite.setPosition(300, 400);
    velocity = 0.f;
}