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
    sf::RenderWindow window;
    sf::Clock clock;

    Bird bird;
    std::vector<Pipe> pipes;

    int score;
    sf::Font font;
    sf::Text scoreText;

    float currentPipeSpeed;
    float currentPipeSpawnInterval;

    float pipeSpawnTimer;
    float totalElapsedTime;
    bool isGameOver;

    void processEvents();
    void update(float deltaTime);
    void render();
    void reset();
};
