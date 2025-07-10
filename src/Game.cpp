#include "Game.hpp"
#include "Config.hpp"
#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(1000, 1000), "Flappy Bird"), pipeSpawnInterval(2.f), pipeSpeed(200.f), score(0), gameOver(false) {
    window.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(nullptr)));
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        if (!gameOver) update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (flapClock.getElapsedTime().asSeconds() > flapCooldown) {
                bird.flap();
                flapClock.restart();
            }
        }
    }
}


void Game::update(float dt) {
    totalElapsedTime += dt;
    bird.update(dt);

    if (spawnClock.getElapsedTime().asSeconds() > pipeSpawnInterval) {
        float GAP = 200.f;
        float scale = 5.f;
        float pipeTextureHeight = 160.f; // укажи точную высоту своей текстуры!
        float pipeHeight = pipeTextureHeight * scale;

        float minGapY = PIPE_GAP / 2 + PIPE_MARGIN;
        float maxGapY = WINDOW_HEIGHT - PIPE_GAP / 2 - PIPE_MARGIN;
        float gapY = rand() % static_cast<int>(maxGapY - minGapY + 1) + minGapY;

        float moveChance = std::min(INITIAL_MOVING_PIPE_CHANCE + totalElapsedTime * MOVING_PIPE_CHANCE_GROWTH, MAX_MOVING_PIPE_CHANCE);

        bool shouldMove = (static_cast<float>(rand()) / RAND_MAX) < moveChance;
        pipes.emplace_back(WINDOW_WIDTH, gapY, totalElapsedTime, shouldMove);
        spawnClock.restart();
    }

    for (auto& pipe : pipes)
        pipe.update(dt);

    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& p) { return p.isOffScreen(); }), pipes.end());

    for (auto& bonus : bonuses)
        bonus.update(dt, pipeSpeed);

    bonuses.erase(std::remove_if(bonuses.begin(), bonuses.end(), [](const Bonus& b) { return b.isOffScreen(); }), bonuses.end());

    for (const auto& pipe : pipes) {
        if (bird.getBounds().intersects(pipe.getTopBounds()) || bird.getBounds().intersects(pipe.getBottomBounds())) {
            gameOver = true;
        }
    }

    for (auto it = bonuses.begin(); it != bonuses.end();) {
        if (bird.getBounds().intersects(it->getBounds())) {
            if (it->getType() == BonusType::Coin) score++;
            else gameOver = true;
            it = bonuses.erase(it);
        } else ++it;
    }

    if (score > 0 && score % 10 == 0)
        pipeSpeed += 10.f;
}

void Game::render() {
    window.clear(sf::Color::Cyan);
    bird.draw(window);
    for (auto& pipe : pipes) pipe.draw(window);
    for (auto& bonus : bonuses) bonus.draw(window);
    window.display();
}

void Game::reset() {
    bird.reset();
    pipes.clear();
    bonuses.clear();
    score = 0;
    pipeSpeed = 200.f;
    gameOver = false;
    spawnClock.restart();
    gameClock.restart();
}
