#pragma once

#include <flecs.h>
#include <raylib.h>

namespace game::Space
{
struct PositionComponent {
	Vector2 val;
};

struct VelocityComponent {
	Vector2 val;
};

struct RotationComponent {
	float val;
};

struct SizeComponent {
	int width;
	int height;
};

void Init(const flecs::world& ecs);

}// namespace game::Space
