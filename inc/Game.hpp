#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include "Pipe.hpp"
#include "Func.hpp"
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

    sf::Texture backgroundTextures[4];
    sf::Sprite backgroundSpriteCurrent;
    sf::Sprite backgroundSpriteNext;

    TimeOfDay currentTimeOfDay;
    TimeOfDay nextTimeOfDay;
    float dayPhaseTimer;      
    float transitionProgress; 
    bool inTransition;

    void processEvents();
    void update(float deltaTime);
    void render();
    void reset();
};

