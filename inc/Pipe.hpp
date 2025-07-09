#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float x, float gapY);
    void update(float dt, float speed);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;

private:
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    sf::Texture texture;
    float oscillationOffset;
    bool movingUp;
};