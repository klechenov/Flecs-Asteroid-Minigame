#pragma once

#include <flecs.h>
#include <raylib.h>

namespace game::Rendering
{
struct Visual final {
	Texture2D texture;
};

void Init(const flecs::world& ecs);

}// namespace game::Rendering
