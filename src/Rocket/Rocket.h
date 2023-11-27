#pragma once

#include <flecs.h>
#include <raylib.h>

namespace game::Rocket
{
// Tag
struct Rocket final {
};

void Init(const flecs::world& ecs);
void FireRocket(const flecs::world& ecs, const Vector2& shipPosition, const float shipRotation);

}// namespace game::Rocket
