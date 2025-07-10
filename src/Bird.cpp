#include "Bird.hpp"
#include "Config.hpp"


Bird::Bird() : velocity(0.f) {
    static sf::Texture sharedTexture;
    static bool loaded = false;
    if (!loaded) {
        loaded = sharedTexture.loadFromFile("assets/bird.png");
        if (!loaded) {
        }
    }
    texture = sharedTexture;
    sprite.setTexture(texture);
    sprite.setScale(4.f,4.f);
    sprite.setPosition(300, 400);
}

void Bird::update(float dt) {
    velocity += GRAVITY * dt;
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