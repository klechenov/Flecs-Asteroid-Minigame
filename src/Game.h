#pragma once

#include <flecs.h>

namespace game
{

class Game
{
public:
	explicit Game();
	void Start();

private:
	flecs::world mEcs{};
};

} // namespace game