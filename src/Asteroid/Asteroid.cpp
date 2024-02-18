#include "Asteroid.h"

#include "Collision/Collision.h"
#include "Rendering/Renderer.h"
#include "Rocket/Rocket.h"
#include "Ship/Ship.h"
#include "Space/Space.h"

#include <cmath>

namespace game::Asteroid
{
using Velocity = Space::VelocityComponent;
using Position = Space::PositionComponent;
using Rotation = Space::RotationComponent;
using Size = Space::SizeComponent;
using Visual = Rendering::VisualComponent;

void Init(const flecs::world& ecs)
{
	ecs.component<AsteroidType>("AsteroidType").add(flecs::Union);

	ecs.prefab<AsteroidPrefabTag>("PrefabAsteroid")
			.add<AsteroidTag>()
			.add<Collision::CollisionRelationship, Ship::ShipTag>()
			.add<Collision::CollisionRelationship, Rocket::RocketTag>()
			.emplace_override<Visual>(2, LoadTexture("res/asteroid.png"))
			.set_override<Size>({0, 0})
			.set_override<AsteroidType>({AsteroidType::None});

	ecs.prefab<BigAsteroidPrefabTag>("PrefabBigAsteroid")
			.is_a<AsteroidPrefabTag>()
			.set<Size>({BIG_ASTEROID_WIDTH, BIG_ASTEROID_HEIGHT})
			.set<AsteroidType>({AsteroidType::Big});

	ecs.prefab<MediumAsteroidPrefabTag>("PrefabMediumAsteroid")
			.is_a<AsteroidPrefabTag>()
			.set<Size>({MEDIUM_ASTEROID_WIDTH, MEDIUM_ASTEROID_HEIGHT})
			.set<AsteroidType>({AsteroidType::Medium});

	ecs.prefab<SmallAsteroidPrefabTag>("PrefabSmallAsteroid")
			.is_a<AsteroidPrefabTag>()
			.set<Size>({SMALL_ASTEROID_WIDTH, SMALL_ASTEROID_HEIGHT})
			.set<AsteroidType>({AsteroidType::Small});

	SpawnAsteroids<BigAsteroidPrefabTag>(ecs, QUANTITY_INIT_ASTEROIDS);
}

void HandleAsteroidDestroyed(flecs::entity asteroid)
{
	const AsteroidType* type = asteroid.get<AsteroidType>();
	const Position* position = asteroid.get<Position>();

	switch (*type)
	{
		case AsteroidType::Big:
			SpawnAsteroids<MediumAsteroidPrefabTag>(asteroid.world(), QUANTITY_AFTER_DESTROY_ASTEROIDS, false, position->val);
			break;
		case AsteroidType::Medium:
			SpawnAsteroids<SmallAsteroidPrefabTag>(asteroid.world(), QUANTITY_AFTER_DESTROY_ASTEROIDS, false, position->val);
			break;
		case AsteroidType::Small:
		default:
			break;
	}
}

std::optional<Vector2> GenerateSafeAsteroidPosition(const flecs::world& ecs, const Vector2& shipPosition)
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	const float safeZoneLeft = std::max(shipPosition.x - SAFE_ZONE_HALF_SIZE, 0.0f);
	const float safeZoneRight = std::min(shipPosition.x + SAFE_ZONE_HALF_SIZE, static_cast<float>(screenWidth));
	const float safeZoneTop = std::max(shipPosition.y - SAFE_ZONE_HALF_SIZE, 0.0f);
	const float safeZoneBottom = std::min(shipPosition.y + SAFE_ZONE_HALF_SIZE, static_cast<float>(screenHeight));

	Vector2 asteroidPosition;
	const int side = GetRandomValue(0, 3);
	switch (side)
	{
		case 0:
			asteroidPosition.x = static_cast<float>(GetRandomValue(0, screenWidth));
			asteroidPosition.y = static_cast<float>(GetRandomValue(0, static_cast<int>(safeZoneTop)));
			break;
		case 1:
			asteroidPosition.x = static_cast<float>(GetRandomValue(0, screenWidth));
			asteroidPosition.y = static_cast<float>(GetRandomValue(static_cast<int>(safeZoneBottom), screenHeight));
			break;
		case 2:
			asteroidPosition.x = static_cast<float>(GetRandomValue(0, static_cast<int>(safeZoneLeft)));
			asteroidPosition.y = static_cast<float>(GetRandomValue(0, screenHeight));
			break;
		case 3:
			asteroidPosition.x = static_cast<float>(GetRandomValue(static_cast<int>(safeZoneRight), screenWidth));
			asteroidPosition.y = static_cast<float>(GetRandomValue(0, screenHeight));
			break;
		default:
			break;
	}

	return asteroidPosition;
}


}// namespace game::Asteroid
