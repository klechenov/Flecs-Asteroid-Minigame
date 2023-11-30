#pragma once

#include <flecs.h>

namespace game::Asteroid
{

struct AsteroidTag {
};

struct AsteroidPrefabTag {
};

void Init(const flecs::world& ecs);
void SpawnAsteroids(const flecs::world& ecs);
}// namespace game::Asteroid
