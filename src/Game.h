#pragma once

#include <flecs.h>
#include <raylib.h>

#include "Space/Space.h"

namespace game
{

class Game final
{
public:
	explicit Game();
	void Start();

private:
	flecs::world mEcs{};
};

}// namespace game
