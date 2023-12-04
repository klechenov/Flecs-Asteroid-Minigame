#pragma once

#include "Globals.h"

#include <flecs.h>
#include <raylib.h>

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

template<typename T>
void SpawnAsteroids(const flecs::world& ecs, size_t quantity, bool randomPosition = true, const Vector2& position = Vector2())
{
	for (size_t i = 0; i < quantity; ++i)
	{
		Vector2 asteroidPosition;
		if (randomPosition)
		{
			asteroidPosition = {static_cast<float>(GetRandomValue(0, GetScreenWidth())),
								static_cast<float>(GetRandomValue(0, GetScreenHeight()))};
		}
		else
		{
			asteroidPosition = position;
		}

		const float rotation = GetRandomValue(0, 360) * DEG2RAD;
		Vector2 velocity = {std::cos(rotation) * AsteroidSpeed<T>::GetSpeed(), std::sin(rotation) * AsteroidSpeed<T>::GetSpeed()};

		ecs.entity()
				.is_a(ecs.prefab<T>())
				.emplace<Position>(asteroidPosition)
				.emplace<Velocity>(velocity)
				.emplace<Rotation>(rotation);
	}
}
}// namespace game::Asteroid
