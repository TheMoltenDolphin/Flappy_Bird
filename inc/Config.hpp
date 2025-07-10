#pragma once

// ---------- Окно ----------
inline constexpr int WINDOW_WIDTH = 1000;
inline constexpr int WINDOW_HEIGHT = 1000;

// ---------- Птица ----------
inline constexpr float GRAVITY = 1000.f;
inline constexpr float FLAP_VELOCITY = -400.f;
inline constexpr float FLAP_COOLDOWN = 0.15f;

// ---------- Трубы ----------
inline constexpr float PIPE_SPEED = 200.f;
inline constexpr float PIPE_SPAWN_INTERVAL = 2.f;
inline constexpr float PIPE_SCALE = 3.f;
inline constexpr float PIPE_GAP = 400.f;
inline constexpr float PIPE_MARGIN = 50.f;

// ---------- Подвижные трубы ----------
inline constexpr float PIPE_MOVE_DELAY = 1.5f;
inline constexpr float PIPE_MOVE_SPEED = 50.f;
inline constexpr float PIPE_INITIAL_OFFSET_RANGE = 60.f;
inline constexpr float PIPE_MAX_OFFSET_RANGE = 160.f;
inline constexpr float PIPE_OFFSET_GROWTH_RATE = 2.f;

// ---------- Вероятность движущихся труб ----------
inline constexpr float INITIAL_MOVING_PIPE_CHANCE = 0.1f;
inline constexpr float MAX_MOVING_PIPE_CHANCE = 0.7f;
inline constexpr float MOVING_PIPE_CHANCE_GROWTH = 1.f / 60.f;
