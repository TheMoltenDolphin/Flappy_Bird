#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float x, float gapY, float gameTime, bool moving = false);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;
    float getX() const;
    bool isOffScreen() const;
    bool hasPassed(float birdX);
    void setSpeed(float speed);



private:
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;

    bool isMoving;
    bool hasStartedMoving;
    float targetOffsetY;
    float currentOffsetY;
    float moveSpeed;
    float currentMovingPipeDelay;
    sf::Clock movementDelayClock;
    bool scored = false;

};
