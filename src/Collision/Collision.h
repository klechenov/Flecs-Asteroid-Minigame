#pragma once

#include "Game.h"
#include "Space/Space.h"

#include <flecs.h>
#include <raylib.h>

namespace game::Collision
{
using Position = Space::PositionComponent;
using Size = Space::SizeComponent;

struct AABB {
	Vector2 min;// top-left
	Vector2 max;// bottom-right
};

struct CollisionRelationship {
};

struct CollidedWith {
};

void Init(const flecs::world& ecs);
AABB CalculateAABB(const Position& center, const Size& size);
bool IsColliding(const AABB& aabb1, const AABB& aabb2);

}// namespace game::Collision
