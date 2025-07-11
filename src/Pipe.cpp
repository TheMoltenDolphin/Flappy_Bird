#include "Pipe.hpp"
#include "Config.hpp"
#include <iostream>
#include <cmath>

Pipe::Pipe(float x, float gapY, float gameTime, bool moving)
    : isMoving(moving),
      hasStartedMoving(false),
      currentOffsetY(0.f),
      moveSpeed(MOVING_PIPE_SPEED),
      currentMovingPipeDelay(MOVING_PIPE_DELAY_BEFORE_MOVING_START)
{
    static sf::Texture sharedTexture;
    static bool loaded = false;
    if (!loaded) {
        if (!sharedTexture.loadFromFile("assets/pipe.png")) {
            std::cerr << "Ошибка загрузки pipe.png\n";
        }
        loaded = true;
    }

    topPipe.setTexture(sharedTexture);
    bottomPipe.setTexture(sharedTexture);
    topPipe.setScale(PIPE_SCALE, PIPE_SCALE);
    bottomPipe.setScale(PIPE_SCALE, PIPE_SCALE);

    sf::Vector2u texSize = sharedTexture.getSize();
    float pipeHeight = texSize.y * PIPE_SCALE;

    topPipe.setOrigin(texSize.x, texSize.y);
    topPipe.setRotation(180);

    topPipe.setPosition(x, gapY - PIPE_GAP / 2.f - pipeHeight);
    bottomPipe.setPosition(x, gapY + PIPE_GAP / 2.f);

    if (isMoving) {
        float maxOffset = std::min(
            MOVING_PIPE_INITIAL_OFFSET + gameTime * MOVING_PIPE_OFFSET_GROWTH,
            MOVING_PIPE_MAX_OFFSET
        );

        targetOffsetY = static_cast<float>((rand() % static_cast<int>(maxOffset * 2 + 1)) - maxOffset);
        movementDelayClock.restart();
    }
}

void Pipe::update(float deltaTime)
{
    // Движение трубы влево
    topPipe.move(-moveSpeed * deltaTime, 0);
    bottomPipe.move(-moveSpeed * deltaTime, 0);

    currentMovingPipeDelay += MOVING_PIPE_DELAY_BEFORE_MOVING_ACCELERATION * deltaTime;
    if (currentMovingPipeDelay > MOVING_PIPE_DELAY_BEFORE_MOVING_MAX)
        currentMovingPipeDelay = MOVING_PIPE_DELAY_BEFORE_MOVING_MAX;


    // Обработка движения подвижных труб
    if (isMoving) {
        if (movementDelayClock.getElapsedTime().asSeconds() > currentMovingPipeDelay && !hasStartedMoving) {
            hasStartedMoving = true;
        }

        if (hasStartedMoving && std::abs(currentOffsetY - targetOffsetY) > 1.f) {
            float direction = (targetOffsetY > currentOffsetY) ? 1.f : -1.f;
            float moveStep = direction * moveSpeed * deltaTime;

            if (std::abs(moveStep) > std::abs(targetOffsetY - currentOffsetY)) {
                moveStep = targetOffsetY - currentOffsetY;
            }

            topPipe.move(0, moveStep*MOVING_PIPE_SPEED);
            bottomPipe.move(0, moveStep*MOVING_PIPE_SPEED);
            currentOffsetY += moveStep;
        }
    }
}

void Pipe::draw(sf::RenderWindow& window)
{
    window.draw(topPipe);
    window.draw(bottomPipe);
}

sf::FloatRect Pipe::getTopBounds() const
{
    return topPipe.getGlobalBounds();
}

sf::FloatRect Pipe::getBottomBounds() const
{
    return bottomPipe.getGlobalBounds();
}

float Pipe::getX() const
{
    return bottomPipe.getPosition().x;
}

bool Pipe::isOffScreen() const
{
    return getX() + topPipe.getGlobalBounds().width < 0;
}

bool Pipe::hasPassed(float birdX)
{
    if (!scored && getX() + topPipe.getGlobalBounds().width < birdX) {
        scored = true;
        return true;
    }
    return false;
}

void Pipe::setSpeed(float speed) {
    moveSpeed = speed;
}

