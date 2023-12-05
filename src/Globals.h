#pragma once

namespace game
{

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr int FPS = 144;
constexpr const char* TITLE = "Asteroids";

constexpr float SHIP_ACCELERATION = 400.f;
constexpr float SPACE_FRICTION = .5f;
constexpr float SHIP_ROTATION_SPEED = 360.f;
constexpr int SHIP_WIDTH = 180;
constexpr int SHIP_HEIGHT = 180;

constexpr int ROCKET_WIDTH = 44;
constexpr int ROCKET_HEIGHT = 76;
constexpr float ROCKET_SPEED = 1000.f;

constexpr int BIG_ASTEROID_WIDTH = 75;
constexpr int BIG_ASTEROID_HEIGHT = 75;
constexpr float BIG_ASTEROID_SPEED = 100.f;
constexpr int MEDIUM_ASTEROID_WIDTH = 45;
constexpr int MEDIUM_ASTEROID_HEIGHT = 45;
constexpr float MEDIUM_ASTEROID_SPEED = 150.f;
constexpr int SMALL_ASTEROID_WIDTH = 25;
constexpr int SMALL_ASTEROID_HEIGHT = 25;
constexpr float SMALL_ASTEROID_SPEED = 200.f;
constexpr size_t QUANTITY_INIT_ASTEROIDS = 6;
constexpr size_t QUANTITY_AFTER_DESTROY_ASTEROIDS = 2;

}// namespace game
