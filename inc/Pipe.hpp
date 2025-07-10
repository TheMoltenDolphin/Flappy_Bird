#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:

    Pipe(float x, float gapY, float gameTime, bool moving = false);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;

private:

    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    float oscillationOffset;
    bool movingUp;
    bool isMoving;
    bool hasStartedMoving;
    float targetOffsetY;
    float currentOffsetY;
    float moveSpeed;
    sf::Clock movementDelayClock;

};