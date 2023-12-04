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
			.emplace<Visual>(2, LoadTexture("res/asteroid.png"))
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


}// namespace game::Asteroid
