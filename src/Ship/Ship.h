#pragma once

#include <flecs.h>
#include <raylib.h>

namespace game::Ship
{
// Tag
struct Ship final {
};

void Init(const flecs::world& ecs);
}// namespace game::Ship
