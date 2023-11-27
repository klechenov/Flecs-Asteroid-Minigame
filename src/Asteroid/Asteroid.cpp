#include "Asteroid.h"

#include "Globals.h"
#include "Rendering/Renderer.h"
#include "Space/Space.h"

#include <cmath>
#include <raylib.h>

namespace game::Asteroid
{
using Velocity = game::Space::Velocity;
using Position = game::Space::Position;
using Size = game::Space::Size;
using Visual = game::Rendering::Visual;

void Init(const flecs::world& ecs)
{
	ecs.prefab("PAsteroid")
			.add<Asteroid>()
			.set<Visual>({LoadTexture("res/asteroid.png")})
			.set<Size>({ASTEROID_WIDTH, ASTEROID_HEIGHT});

	SpawnAsteroids(ecs);

	ecs.system<Asteroid, Velocity, Position>("AsteroidMovement")
			.kind(flecs::OnUpdate)
			.each([](Asteroid&, Velocity& vel, Position& pos) {
				float deltaTime = GetFrameTime();
				pos.val.x += vel.val.x * deltaTime;
				pos.val.y += vel.val.y * deltaTime;
			});
}

// TODO: Temporary. Implement system that handle asteroids spawning
void SpawnAsteroids(const flecs::world& ecs)
{
	for (size_t i = 0; i < 6; ++i)
	{
		const Vector2 position = {static_cast<float>(GetRandomValue(0, GetScreenWidth())),
								  static_cast<float>(GetRandomValue(0, GetScreenHeight()))};
		const float angle = GetRandomValue(0, 360) * DEG2RAD;
		Vector2 velocity = {std::cos(angle) * BIG_ASTEROID_SPEED, std::sin(angle) * BIG_ASTEROID_SPEED};

		ecs.entity()
				.is_a(ecs.prefab("PAsteroid"))
				.set<Position>({position})
				.set<Velocity>({velocity});
	}
}

}// namespace game::Asteroid
