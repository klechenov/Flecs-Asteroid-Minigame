#pragma once

#include <flecs.h>

namespace game::Ship
{

struct ShipTag {
};

void Init(const flecs::world& ecs);
}// namespace game::Ship
