#include "Rocket.h"

#include "Asteroid/Asteroid.h"
#include "Collision/Collision.h"
#include "Globals.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "Space/Space.h"

#include <cmath>

namespace game::Rocket
{
using Velocity = Space::VelocityComponent;
using Position = Space::PositionComponent;
using Rotation = Space::RotationComponent;
using Size = Space::SizeComponent;
using Visual = Rendering::VisualComponent;

void FireRocket(const flecs::world& ecs, const Vector2& shipPosition, const float shipRotation)
{
	const float rad = shipRotation * DEG2RAD;
	const Vector2 rocketVelocity = {std::sin(rad) * ROCKET_SPEED, -std::cos(rad) * ROCKET_SPEED};

	ecs.entity()
			.is_a(ecs.prefab<RocketPrefabTag>())
			.emplace<Position>(shipPosition)
			.emplace<Velocity>(rocketVelocity)
			.emplace<Rotation>(shipRotation);
}

void Init(const flecs::world& ecs)
{
	ecs.prefab<RocketPrefabTag>("PrefabRocket")
			.add<RocketTag>()
			.add<Collision::CollisionRelationship, Asteroid::AsteroidTag>()
			.emplace<Visual>(0, LoadTexture("res/rocket.png"))
			.emplace<Size>(ROCKET_WIDTH, ROCKET_HEIGHT);
}

}// namespace game::Rocket
