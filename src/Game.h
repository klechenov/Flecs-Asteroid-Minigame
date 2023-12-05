#pragma once

#include <flecs.h>
#include <raylib.h>

#include "Space/Space.h"

namespace game
{

using CollisionSystemQuery = flecs::query<const Space::PositionComponent, const Space::SizeComponent>;

class Game final
{
public:
	explicit Game();
	void Start();

private:
	flecs::world mEcs{};
	CollisionSystemQuery mCollisionSystemQuery{};
};

}// namespace game
