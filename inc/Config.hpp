#pragma once

// 🖼 Размер окна
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

// 🐦 Птица
const float BIRD_GRAVITY = 1000.f;
const float BIRD_JUMP_VELOCITY = -600.f;
const float BIRD_SCALE = 5.f;

// 🚧 Трубы
const float PIPE_SCALE = 5.f;
const float PIPE_GAP = 400.f;

// Скорость труб
inline constexpr float PIPE_SPEED_START = 200.f;      // стартовая скорость движения труб (px/sec)
inline constexpr float PIPE_SPEED_MAX = 600.f;        // максимальная скорость труб
inline constexpr float PIPE_SPEED_ACCELERATION = 5.f; // скорость увеличения (px/sec^2)

// Интервал появления труб
inline constexpr float PIPE_SPAWN_INTERVAL_START = 2.f; // стартовый интервал (сек)
inline constexpr float PIPE_SPAWN_INTERVAL_MIN = 0.5f;   // минимальный интервал
inline constexpr float PIPE_SPAWN_ACCELERATION = 0.025f;  // увеличение интервала в секунду


// 🎯 Ограничения на генерацию труб
const float PIPE_MIN_GAP_Y = PIPE_GAP / 2 + 50.f;
const float PIPE_MAX_GAP_Y = WINDOW_HEIGHT - PIPE_GAP / 2 - 50.f;

// ⚙️ Движущиеся трубы
const float MOVING_PIPE_INITIAL_CHANCE = 0.1f;  // 10%
const float MOVING_PIPE_MAX_CHANCE = 0.7f;      // 70%
const float MOVING_PIPE_CHANCE_GROWTH = 1.f / 60.f; // +1% в сек

const float MOVING_PIPE_INITIAL_OFFSET = 120.f;
const float MOVING_PIPE_MAX_OFFSET = 320.f;
const float MOVING_PIPE_OFFSET_GROWTH = 2.f; // +2 пикс/сек

const float MOVING_PIPE_DELAY_BEFORE_MOVING_START = 1.5f;
const float MOVING_PIPE_DELAY_BEFORE_MOVING_MAX = 0.7f;
const float MOVING_PIPE_DELAY_BEFORE_MOVING_ACCELERATION = 0.0375f;
const float MOVING_PIPE_SPEED = 100.f; // пикс/сек

// 🔘 Управление
const float INPUT_COOLDOWN = 0.25f;
