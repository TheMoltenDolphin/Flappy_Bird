#pragma once
#include <SFML/Graphics.hpp>

class Bird {
public:
    Bird();

    void update(float deltaTime);
    void jump();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset();

private:
    sf::Sprite sprite;
    float velocity;
    float inputCooldown;
};
