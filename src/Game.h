#pragma once

#include <flecs.h>
#include <raylib.h>

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
