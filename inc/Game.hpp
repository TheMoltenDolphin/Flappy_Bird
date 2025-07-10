#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include "Pipe.hpp"
#include "Bonus.hpp"
#include <vector>

class Game {
public:

    Game();
    void run();

private:

    void processEvents();
    void update(float dt);
    void render();
    void reset();

    
    sf::RenderWindow window;
    Bird bird;
    std::vector<Pipe> pipes;
    std::vector<Bonus> bonuses;
    sf::Clock spawnClock;
    sf::Clock gameClock;
    sf::Clock flapClock;
    const float flapCooldown = 0.25f;
    float totalElapsedTime = 0.f;
    float pipeSpawnInterval;
    float pipeSpeed;
    int score;
    bool gameOver;
};