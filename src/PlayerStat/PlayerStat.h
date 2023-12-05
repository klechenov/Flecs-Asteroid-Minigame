#pragma once

#include <flecs.h>

namespace game::PlayerStat
{

struct PlayerStatSingleton {
	int hp;
	int score;
};

void Init(const flecs::world& ecs);

}// namespace game::PlayerStat
