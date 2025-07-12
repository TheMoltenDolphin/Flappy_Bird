#pragma once

// Размер окна
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// Птица
const float BIRD_GRAVITY = 1000.f;
const float BIRD_JUMP_VELOCITY = -500.f;
const float BIRD_SCALE = 5.f;

// Трубы
const float PIPE_SCALE = 5.f;
const float PIPE_GAP = 400.f;

// Скорость труб
inline constexpr float PIPE_SPEED_START = 200.f;      // стартовая скорость движения труб
inline constexpr float PIPE_SPEED_MAX = 600.f;        // максимальная скорость труб
inline constexpr float PIPE_SPEED_ACCELERATION = 5.f; // скорость увеличения в секунду

// Интервал появления труб
inline constexpr float PIPE_SPAWN_INTERVAL_START = 2.f; // стартовый интервал
inline constexpr float PIPE_SPAWN_INTERVAL_MIN = 0.5f;   // минимальный интервал
inline constexpr float PIPE_SPAWN_ACCELERATION = 0.025f ;  // увеличение интервала в секунду


// Ограничения на генерацию труб
const float PIPE_MIN_GAP_Y = PIPE_GAP;
const float PIPE_MAX_GAP_Y = WINDOW_HEIGHT - PIPE_GAP;

// Движущиеся трубы
const float MOVING_PIPE_INITIAL_CHANCE = 0.01f;  // 1%
const float MOVING_PIPE_MAX_CHANCE = 0.7f;      // 70%
const float MOVING_PIPE_CHANCE_GROWTH = 0.5f / 60.f; // 0.25% в сек

const float MOVING_PIPE_INITIAL_OFFSET = 240.f;
const float MOVING_PIPE_MAX_OFFSET = 120.f;
const float MOVING_PIPE_OFFSET_GROWTH = -10.f; // -10 пикс/сек

const float MOVING_PIPE_DELAY_BEFORE_MOVING_START = 2.f;
const float MOVING_PIPE_DELAY_BEFORE_MOVING_MAX = 1.f;
const float MOVING_PIPE_DELAY_BEFORE_MOVING_ACCELERATION = 0.0375f;
const float MOVING_PIPE_SPEED = 2.f; // множитель скорости

// Управление
const float INPUT_COOLDOWN = 0.25f;
const float DAY_PHASE_DURATION = 10.f;
const float PHASE_TRANSITION_DURATION = 3.f;

