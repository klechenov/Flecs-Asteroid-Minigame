#pragma once

#include <flecs.h>
#include <raylib.h>
#include <optional>

#include "Globals.h"
#include "Space/Space.h"

namespace game::Asteroid
{

enum class AsteroidType
{
	None = 0,
	Small,
	Medium,
	Big
};

struct AsteroidTag {
};

struct AsteroidPrefabTag {
};

struct BigAsteroidPrefabTag {
};

struct MediumAsteroidPrefabTag {
};

struct SmallAsteroidPrefabTag {
};

template<typename T>
class AsteroidSpeed;

template<>
class AsteroidSpeed<BigAsteroidPrefabTag>
{
public:
	static float GetSpeed()
	{
		return BIG_ASTEROID_SPEED;
	}
};

template<>
class AsteroidSpeed<MediumAsteroidPrefabTag>
{
public:
	static float GetSpeed()
	{
		return MEDIUM_ASTEROID_SPEED;
	}
};

template<>
class AsteroidSpeed<SmallAsteroidPrefabTag>
{
public:
	static float GetSpeed()
	{
		return SMALL_ASTEROID_SPEED;
	}
};

void Init(const flecs::world& ecs);
void HandleAsteroidDestroyed(flecs::entity);

std::optional<Vector2> GenerateSafeAsteroidPosition(const flecs::world& ecs, const Vector2& shipPosition);

template<typename T>
void SpawnAsteroids(const flecs::world& ecs, size_t quantity, bool randomPosition = true, const Vector2& position = Vector2())
{
	for (size_t i = 0; i < quantity; ++i)
	{
		Vector2 asteroidPosition;
		if (randomPosition)
		{
			Vector2 shipPosition;
			auto rule = ecs.rule_builder<const Space::PositionComponent>()
								.with<Ship::ShipTag>()
								.build();
			rule.each([&shipPosition](flecs::entity shipEntity, const Space::PositionComponent& pos) {
				shipPosition = pos.val;
			});
			rule.destruct();

			auto safePosition = GenerateSafeAsteroidPosition(ecs, shipPosition);
			if (safePosition)
			{
				asteroidPosition = *safePosition;
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			asteroidPosition = position;
		}

		const float rotation = static_cast<float>(GetRandomValue(0, 360)) * DEG2RAD;
		const Vector2 velocity = {std::cos(rotation) * AsteroidSpeed<T>::GetSpeed(), std::sin(rotation) * AsteroidSpeed<T>::GetSpeed()};

		ecs.entity()
				.is_a(ecs.prefab<T>())
				.emplace<Position>(asteroidPosition)
				.emplace<Velocity>(velocity)
				.emplace<Rotation>(rotation);
	}
}
}// namespace game::Asteroid
