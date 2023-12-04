#include "PlayerStat.h"

namespace game::PlayerStat
{

void Init(const flecs::world& ecs)
{
	ecs.singleton<PlayerStatSingleton>();
}

}// namespace game::PlayerStat