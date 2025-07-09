#include "Pipe.hpp"

Pipe::Pipe(float x, float gapY) : oscillationOffset(0.f), movingUp(true) {
    static sf::Texture sharedTexture;
    static bool loaded = false;
    if (!loaded) {
        sharedTexture.loadFromFile("assets/pipe.png");
        loaded = true;
    }
    topPipe.setTexture(sharedTexture);
    bottomPipe.setTexture(sharedTexture);
    topPipe.setScale(4.f, 4.f);
    bottomPipe.setScale(4.f, 4.f);
    topPipe.setRotation(180);
    topPipe.setPosition(x, gapY - 100 - sharedTexture.getSize().y);
    bottomPipe.setPosition(x-28*topPipe.getScale().x, gapY + 100);
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