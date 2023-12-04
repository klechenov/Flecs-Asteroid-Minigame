#include "Collision.h"

#include "Asteroid/Asteroid.h"
#include "Rocket/Rocket.h"
#include "Ship/Ship.h"

#include <array>
#include <cmath>

namespace game::Collision
{

void Init(const flecs::world& ecs, CollisionSystemQuery& Query)
{
	ecs.component<CollidedWith>("CollidedWith");

	ecs.system<const Position, const Size>("DebugDrawAABB")
			.each([](const Position& pos1, const Size& size1) {
				const AABB aabb = CalculateAABB(pos1, size1);
				const int width = static_cast<int>(aabb.max.x - aabb.min.x);
				const int height = static_cast<int>(aabb.max.y - aabb.min.y);
				DrawRectangleLines(static_cast<int>(aabb.min.x), static_cast<int>(aabb.min.y), width, height, YELLOW);
			});

	Query = ecs.query_builder<const Position, const Size>("CollisionSystemQuery")
					.with<CollisionRelationship>(flecs::Wildcard)
					.build();

	ecs.system<const Position, const Size>("CollisionDetectionSystem")
			.kind(flecs::OnValidate)
			.write<CollidedWith>()
			.ctx(&Query)
			.each([](flecs::iter& it1, size_t index1, const Position& pos1, const Size& size1) {
				const CollisionSystemQuery* q = it1.ctx<CollisionSystemQuery>();
				flecs::entity e1 = it1.entity(index1);

				q->each([&e1, &pos1, &size1](flecs::iter& it2, size_t index2, const Position pos2, const Size size2) {
					flecs::entity e2 = it2.entity(index2);
					if (e1 == e2)
					{
						return;
					}

					if (e1 > e2)
					{
						return;
					}

					flecs::entity tag = it2.pair(3).second();
					if (!e1.has(tag))
					{
						return;
					}

					if (e1.has<CollidedWith>(e2) || e2.has<CollidedWith>(e1))
					{
						return;
					}

					const AABB aabb1 = CalculateAABB(pos1, size1);
					const AABB aabb2 = CalculateAABB(pos2, size2);
					if (IsColliding(aabb1, aabb2))
					{
						e1.add<CollidedWith>(e2);
					}
				});
			});

	ecs.system("CollisionResponseSystem")
			.kind(flecs::PostUpdate)
			.with<CollidedWith>(flecs::Wildcard)
			.write<CollidedWith>()
			.each([](flecs::iter& it, size_t index) {
				flecs::entity e1 = it.entity(index);
				flecs::entity e2 = it.pair(1).second();
				
				//TODO: think about how to implement this not so explicitly

				if (e1.has<Ship::ShipTag>() && e2.has<Asteroid::AsteroidTag>())
				{
					
				}

				if (e1.has<Asteroid::AsteroidTag>() && e2.has<Ship::ShipTag>())
				{
					
				}

				if (e1.has<Asteroid::AsteroidTag>() && e2.has<Rocket::RocketTag>())
				{
					Asteroid::HandleAsteroidDestroyed(e1);
					e1.destruct();
					e2.destruct();
				}

				if (e1.has<Rocket::RocketTag>() && e2.has<Asteroid::AsteroidTag>())
				{
					Asteroid::HandleAsteroidDestroyed(e2);
					e1.destruct();
					e2.destruct();
				}

				e1.remove<CollidedWith>(e2);
			});
}

AABB CalculateAABB(const Position& center, const Size& size)
{
	const float maxDimension = std::max(size.width, size.height);
	const float halfMaxDimension = maxDimension * .5f;

	AABB aabb;
	aabb.min.x = center.val.x - halfMaxDimension;
	aabb.min.y = center.val.y - halfMaxDimension;
	aabb.max.x = center.val.x + halfMaxDimension;
	aabb.max.y = center.val.y + halfMaxDimension;

	return aabb;
}

bool IsColliding(const AABB& aabb1, const AABB& aabb2)
{
	if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x)
	{
		return false;
	}
	if (aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y)
	{
		return false;
	}

	return true;
}

}// namespace game::Collision
