#include "Asteroid.h"

#include "Globals.h"
#include "Rendering/Renderer.h"
#include "Space/Space.h"

#include <cmath>
#include <raylib.h>

namespace game::Asteroid
{
using Velocity = Space::VelocityComponent;
using Position = Space::PositionComponent;
using Size = Space::SizeComponent;
using Visual = Rendering::VisualComponent;

void Init(const flecs::world& ecs)
{
	ecs.component<AsteroidTag>("AsteroidTag");

	ecs.prefab<AsteroidPrefabTag>("PrefabAsteroid")
			.add<AsteroidTag>()
			.emplace<Visual>(2, LoadTexture("res/asteroid.png"))
			.emplace<Size>(ASTEROID_WIDTH, ASTEROID_HEIGHT);

	SpawnAsteroids(ecs);
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
				.is_a(ecs.prefab<AsteroidPrefabTag>())
				.emplace<Position>(position)
				.emplace<Velocity>(velocity);
	}
}

}// namespace game::Asteroid
