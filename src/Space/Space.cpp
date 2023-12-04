#include "Space.h"

#include "Asteroid/Asteroid.h"
#include "Rocket/Rocket.h"
#include "Ship/Ship.h"

namespace game::Space
{

void Init(const flecs::world& ecs)
{
	ecs.component<Asteroid::AsteroidTag>("AsteroidTag");
	ecs.component<Ship::ShipTag>("ShipTag");
	ecs.component<Rocket::RocketTag>("RocketTag");

	ecs.component<PositionComponent>("PositionComponent");

	ecs.component<VelocityComponent>("VelocityComponent");

	ecs.component<RotationComponent>("RotationComponent")
			.member<float>("val");

	ecs.component<SizeComponent>("SizeComponent")
			.member<int>("width")
			.member<int>("height");
}

}// namespace game::Space
