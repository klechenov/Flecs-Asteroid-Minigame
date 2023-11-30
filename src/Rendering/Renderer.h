#pragma once

#include <flecs.h>
#include <raylib.h>

namespace game::Rendering
{

struct VisualComponent {
	int zOrder;
	Texture2D texture;
};

void InitRender(const flecs::world& ecs);
void InitSystems(const flecs::world& ecs);

}// namespace game::Rendering
