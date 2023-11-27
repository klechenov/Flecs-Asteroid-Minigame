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

constexpr int ASTEROID_WIDTH = 75;
constexpr int ASTEROID_HEIGHT = 75;
constexpr float BIG_ASTEROID_SPEED = 200.f;

}// namespace game
