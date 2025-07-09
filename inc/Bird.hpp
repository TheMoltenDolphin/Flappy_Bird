#pragma once
#include <SFML/Graphics.hpp>

class Bird {
public:
    Bird();
    void update(float dt);
    void flap();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float velocity;
    const float gravity = 900.f;
    const float flapStrength = -500.f;
};
