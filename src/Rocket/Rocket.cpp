#include "Rocket.h"

#include "Globals.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "Space/Space.h"

#include <cmath>

namespace game::Rocket
{
using Velocity = game::Space::Velocity;
using Position = game::Space::Position;
using Size = game::Space::Size;
using Visual = game::Rendering::Visual;

void FireRocket(const flecs::world& ecs, const Vector2& shipPosition, const float shipRotation)
{
	const float rad = shipRotation * DEG2RAD;
	const Vector2 rocketVelocity = {std::sin(rad) * ROCKET_SPEED, -std::cos(rad) * ROCKET_SPEED};

	ecs.entity()
			.is_a(ecs.prefab("PRocket"))
			.set<Position>({shipPosition})
			.set<Velocity>({rocketVelocity});
}

void Init(const flecs::world& ecs)
{
	ecs.prefab("PRocket")
			.add<Rocket>()
			.set<Visual>({LoadTexture("res/rocket.png")})
			.set<Size>({ROCKET_WIDTH, ROCKET_HEIGHT});

	ecs.system<Rocket, Velocity, Position>("RocketMovement")
			.kind(flecs::OnUpdate)
			.each([](Rocket&, Velocity& vel, Position& pos) {
				float deltaTime = GetFrameTime();
				pos.val.x += vel.val.x * deltaTime;
				pos.val.y += vel.val.y * deltaTime;
			});
}

}// namespace game::Rocket
