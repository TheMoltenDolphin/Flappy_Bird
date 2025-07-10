#include "Bird.hpp"
#include "Config.hpp"
#include <iostream>

Bird::Bird()
    : velocity(0.f), inputCooldown(0.f)
{
    static sf::Texture sharedTexture;
    static bool loaded = false;
    if (!loaded) {
        if (!sharedTexture.loadFromFile("assets/bird.png")) {
            std::cerr << "Ошибка загрузки bird.png\n";
        }
        loaded = true;
    }

    sprite.setTexture(sharedTexture);
    sprite.setScale(BIRD_SCALE, BIRD_SCALE);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setPosition(WINDOW_WIDTH / 4.f, WINDOW_HEIGHT / 2.f);
}

void Bird::update(float deltaTime)
{
    // Применение гравитации
    velocity += BIRD_GRAVITY * deltaTime;
    sprite.move(0, velocity * deltaTime);

    // Плавный поворот при падении/прыжке (визуальный эффект)
    float rotation = std::min(velocity / 5.f, 90.f); // ограничим наклон вниз
    sprite.setRotation(rotation);

    // Кулдаун для нажатий
    if (inputCooldown > 0.f)
        inputCooldown -= deltaTime;
}

void Bird::jump()
{
    if (inputCooldown <= 0.f) {
        velocity = BIRD_JUMP_VELOCITY;
        inputCooldown = INPUT_COOLDOWN;
    }
}

void Bird::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Bird::reset()
{
    velocity = 0.f;
    inputCooldown = 0.f;

    sprite.setPosition(WINDOW_WIDTH / 4.f, WINDOW_HEIGHT / 2.f);
    sprite.setRotation(0.f);
}
