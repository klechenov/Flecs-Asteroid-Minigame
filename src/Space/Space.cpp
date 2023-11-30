#include "Space.h"

namespace game::Space
{

void Init(const flecs::world& ecs)
{
	ecs.component<PositionComponent>("PositionComponent");

	ecs.component<VelocityComponent>("VelocityComponent");

	ecs.component<RotationComponent>("RotationComponent")
			.member<float>("val");

	ecs.component<SizeComponent>("SizeComponent")
			.member<int>("width")
			.member<int>("height");
}

}// namespace game::Space
