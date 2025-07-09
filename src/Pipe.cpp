#include "Pipe.hpp"

Pipe::Pipe(float x, float gapY) : oscillationOffset(0.f), movingUp(true) {
    texture.loadFromFile("assets/pipe.png");
    topPipe.setTexture(texture);
    bottomPipe.setTexture(texture);
    topPipe.setRotation(180);
    topPipe.setPosition(x, gapY - 200 - texture.getSize().y);
    bottomPipe.setPosition(x, gapY + 200);
}

void Pipe::update(float dt, float speed) {
    float dy = (movingUp ? -1 : 1) * 40 * dt;
    topPipe.move(-speed * dt, dy);
    bottomPipe.move(-speed * dt, dy);

    oscillationOffset += dy;
    if (oscillationOffset > 50 || oscillationOffset < -50) movingUp = !movingUp;
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