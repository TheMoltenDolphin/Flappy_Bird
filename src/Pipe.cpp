#include "Pipe.hpp"
#include "Config.hpp"


Pipe::Pipe(float x, float gapY, float gameTime, bool moving)
    : isMoving(moving),
      hasStartedMoving(false),
      currentOffsetY(0.f),
      moveSpeed(50.f)
{
    static sf::Texture sharedTexture;
    static bool loaded = false;
    if (!loaded) {
        if (!sharedTexture.loadFromFile("assets/pipe.png")) {
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

    topPipe.setPosition(x, gapY - PIPE_GAP / 2 - pipeHeight);
    bottomPipe.setPosition(x, gapY + PIPE_GAP / 2);

    if (isMoving) {
        float maxOffset = std::min(PIPE_INITIAL_OFFSET_RANGE + gameTime * PIPE_OFFSET_GROWTH_RATE, PIPE_MAX_OFFSET_RANGE);
        targetOffsetY = static_cast<float>((rand() % static_cast<int>(maxOffset * 2 + 1)) - maxOffset);
        moveSpeed = PIPE_MOVE_SPEED;
        movementDelayClock.restart();
    }
}



void Pipe::update(float deltaTime) {
    topPipe.move(-PIPE_SPEED * deltaTime, 0);
    bottomPipe.move(-PIPE_SPEED * deltaTime, 0);

    if (isMoving) {
        if (movementDelayClock.getElapsedTime().asSeconds() > PIPE_MOVE_DELAY && !hasStartedMoving) {
            hasStartedMoving = true;
        }

        if (hasStartedMoving && std::abs(currentOffsetY - targetOffsetY) > 1.f) {
            float direction = (targetOffsetY > currentOffsetY) ? 1.f : -1.f;
            float moveStep = direction * moveSpeed * deltaTime;

            if (std::abs(moveStep) > std::abs(targetOffsetY - currentOffsetY))
                moveStep = targetOffsetY - currentOffsetY;

            topPipe.move(0, moveStep);
            bottomPipe.move(0, moveStep);
            currentOffsetY += moveStep;
        }
    }
}



void Pipe::draw(sf::RenderWindow& window) {
    window.draw(topPipe);
    window.draw(bottomPipe);
}

bool Pipe::isOffScreen() const {
    return topPipe.getPosition().x + topPipe.getGlobalBounds().width < 0;
}

sf::FloatRect Pipe::getTopBounds() const {
    return topPipe.getGlobalBounds();
}

sf::FloatRect Pipe::getBottomBounds() const {
    return bottomPipe.getGlobalBounds();
}