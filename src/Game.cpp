#include "Game.hpp"
#include "Config.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>


Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird ++"),
      pipeSpawnTimer(0.f),
      totalElapsedTime(0.f),
      isGameOver(false)
{

    backgroundTextures[0].loadFromFile("assets/evening.jpg");
    backgroundTextures[1].loadFromFile("assets/day.jpg");
    backgroundTextures[2].loadFromFile("assets/evening.jpg");
    backgroundTextures[3].loadFromFile("assets/night.jpg");

    currentTimeOfDay = TimeOfDay::Morning;
    nextTimeOfDay = TimeOfDay::Day;
    dayPhaseTimer = 0.f;
    transitionProgress = 0.f;
    inTransition = false;

    backgroundSpriteCurrent.setTexture(backgroundTextures[static_cast<int>(currentTimeOfDay)]);
    backgroundSpriteNext.setTexture(backgroundTextures[static_cast<int>(nextTimeOfDay)]);

    score = 0;

    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "SOSALSOSALSOSAL\n";
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(72);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(30.f, 20.f);
    scoreText.setString("0");

    currentPipeSpeed = PIPE_SPEED_START;
    currentPipeSpawnInterval = PIPE_SPAWN_INTERVAL_START;

    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::run()
{
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();

        if (!isGameOver) {
            update(deltaTime);
        }

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (!isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            bird.jump();

        if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            reset();
    }
}

void Game::update(float deltaTime)
{
    totalElapsedTime += deltaTime;
    pipeSpawnTimer += deltaTime;

    bird.update(deltaTime);

    // Увеличиваем скорость труб с ограничением
    currentPipeSpeed += PIPE_SPEED_ACCELERATION * deltaTime;
    if (currentPipeSpeed > PIPE_SPEED_MAX)
        currentPipeSpeed = PIPE_SPEED_MAX;

    // Уменьшаем интервал появления труб, но не меньше минимального
    currentPipeSpawnInterval -= PIPE_SPAWN_ACCELERATION * deltaTime;
    if (currentPipeSpawnInterval < PIPE_SPAWN_INTERVAL_MIN)
        currentPipeSpawnInterval = PIPE_SPAWN_INTERVAL_MIN;


    if (pipeSpawnTimer >= currentPipeSpawnInterval) {
        pipeSpawnTimer = 0.f;

        // Вычисление ограниченного Y для трубы
        float gapY = static_cast<float>(rand() % static_cast<int>(PIPE_MAX_GAP_Y - PIPE_MIN_GAP_Y)) + PIPE_MIN_GAP_Y;

        // Вычисляем вероятность появления движущейся трубы
        float moveChance = std::min(
            MOVING_PIPE_INITIAL_CHANCE + totalElapsedTime * MOVING_PIPE_CHANCE_GROWTH,
            MOVING_PIPE_MAX_CHANCE
        );
        bool shouldMove = (static_cast<float>(rand()) / RAND_MAX) < moveChance;

        Pipe newPipe(WINDOW_WIDTH, gapY, totalElapsedTime, shouldMove);
        newPipe.setSpeed(currentPipeSpeed);
        pipes.push_back(newPipe);    
    }

    // Обновляем трубы
    for (auto& pipe : pipes) {
        pipe.update(deltaTime);
    }

    // Удаляем трубы, вышедшие за экран
    pipes.erase(
        std::remove_if(pipes.begin(), pipes.end(),
            [](const Pipe& pipe) { return pipe.isOffScreen(); }),
        pipes.end()
    );

    // Проверка столкновений
    for (const auto& pipe : pipes) {
        if (bird.getBounds().intersects(pipe.getTopBounds()) ||
            bird.getBounds().intersects(pipe.getBottomBounds())) {
            isGameOver = true;
        }
    }
    for (auto& pipe : pipes) {
        if (pipe.hasPassed(bird.getBounds().left)) {
            score++;
            scoreText.setString(std::to_string(score));
        }
    }


    // Проверка выхода за границы
    if (bird.getBounds().top < 0 || bird.getBounds().top + bird.getBounds().height > WINDOW_HEIGHT) {
        isGameOver = true;
    }

    dayPhaseTimer += deltaTime;

    if (!inTransition && dayPhaseTimer >= DAY_PHASE_DURATION) {
        inTransition = true;
        transitionProgress = 0.f;
        dayPhaseTimer = 0.f;
        nextTimeOfDay = getNextTimeOfDay(currentTimeOfDay);
        backgroundSpriteNext.setTexture(backgroundTextures[static_cast<int>(nextTimeOfDay)]);
    }

    if (inTransition) {
        transitionProgress += deltaTime / PHASE_TRANSITION_DURATION;
        if (transitionProgress >= 1.f) {
            transitionProgress = 0.f;
            inTransition = false;
            currentTimeOfDay = nextTimeOfDay;
            backgroundSpriteCurrent.setTexture(backgroundTextures[static_cast<int>(currentTimeOfDay)]);
        }
    }
}

void Game::render()
{
    window.clear(sf::Color::Cyan);


    if (inTransition)
    {
        backgroundSpriteCurrent.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>((1 - transitionProgress) * 255)));
        backgroundSpriteNext.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(transitionProgress * 255)));

        window.draw(backgroundSpriteCurrent);
        window.draw(backgroundSpriteNext);
    }
    else
    {
        backgroundSpriteCurrent.setColor(sf::Color::White);
        window.draw(backgroundSpriteCurrent);
    }

    for (auto& pipe : pipes)
        pipe.draw(window);

    bird.draw(window);
    window.draw(scoreText);

    if (isGameOver) {
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded) {
            if (!font.loadFromFile("assets/arial.ttf"))
                std::cerr << "Не удалось загрузить шрифт\n";
            fontLoaded = true;
        }

        sf::Text text("Game Over! Press R to restart", font, 72);
        text.setFillColor(sf::Color::Red);
        text.setPosition(WINDOW_WIDTH / 2.f - text.getLocalBounds().width / 2.f, WINDOW_HEIGHT / 2.f - 40.f);
        window.draw(text);
    }

    


    window.display();
}

void Game::reset()
{
    bird.reset();
    pipes.clear();
    pipeSpawnTimer = 0.f;
    totalElapsedTime = 0.f;
    score = 0;
    scoreText.setString("0");
    isGameOver = false;
    currentPipeSpeed = PIPE_SPEED_START;
    currentPipeSpawnInterval = PIPE_SPAWN_INTERVAL_START;
}