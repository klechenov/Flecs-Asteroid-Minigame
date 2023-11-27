#pragma once

#include <flecs.h>

namespace game::Asteroid
{
// Tag
struct Asteroid final {
};

void Init(const flecs::world& ecs);
void SpawnAsteroids(const flecs::world& ecs);
}// namespace game::Asteroid
