#include "Game.h"

#include <raylib.h>

#include "Asteroid/Asteroid.h"
#include "Collision/Collision.h"
#include "Input/Input.h"
#include "PlayerStat/PlayerStat.h"
#include "Rendering/Renderer.h"
#include "Rocket/Rocket.h"
#include "Ship/Ship.h"
#include "Space/Space.h"

namespace game
{
void Init(const flecs::world& ecs)
{
	ecs.system<const Space::VelocityComponent, Space::PositionComponent>("EntitiesMovement")
			.kind(flecs::OnUpdate)
			.with<Rocket::RocketTag>()
			.oper(flecs::Or)
			.with<Asteroid::AsteroidTag>()
			.each([](const Space::VelocityComponent& vel, Space::PositionComponent& pos) {
				float deltaTime = GetFrameTime();
				pos.val.x += vel.val.x * deltaTime;
				pos.val.y += vel.val.y * deltaTime;
			});

	ecs.system<const Space::SizeComponent, Space::PositionComponent>("OffScreenSystem")
			.kind(flecs::PreUpdate)
			.term<game::Rocket::RocketTag>()
			.oper(flecs::Or)
			.term<game::Asteroid::AsteroidTag>()
			.oper(flecs::Or)
			.term<game::Ship::ShipTag>()
			.each([](flecs::entity e, const Space::SizeComponent& size, Space::PositionComponent& pos) {
				const int screenWidth = GetScreenWidth();
				const int screenHeight = GetScreenHeight();

				const bool offScreen = pos.val.x + size.width * .5f < 0 ||
						pos.val.x - size.width * .5f > screenWidth ||
						pos.val.y + size.height * .5f < 0 ||
						pos.val.y - size.height * .5f > screenHeight;

				if (!offScreen)
				{
					return;
				}

				if (e.has<game::Rocket::RocketTag>())
				{
					e.destruct();
				}
				else if ((e.has<game::Asteroid::AsteroidTag>() || e.has<game::Ship::ShipTag>()))
				{
					if (pos.val.x < 0)
					{
						pos.val.x = screenWidth;
					}
					else if (pos.val.x > screenWidth)
					{
						pos.val.x = 0;
					}
					if (pos.val.y < 0)
					{
						pos.val.y = screenHeight;
					}
					else if (pos.val.y > screenHeight)
					{
						pos.val.y = 0;
					}
				}
			});
}

Game::Game()
{
	mEcs.set<flecs::Rest>({});
	flecs::log::set_level(0);
	mEcs.import <flecs::monitor>();

	game::Rendering::InitRender(mEcs);
	game::Input::Init(mEcs);
	game::Space::Init(mEcs);
	game::PlayerStat::Init(mEcs);
	game::Collision::Init(mEcs, mCollisionSystemQuery);
	game::Ship::Init(mEcs);
	game::Rocket::Init(mEcs);
	game::Asteroid::Init(mEcs);
	game::Init(mEcs);
	game::Rendering::InitSystems(mEcs);
}

void Game::Start()
{
	while (mEcs.progress(GetFrameTime()))
	{
		if (WindowShouldClose())
			mEcs.quit();
	}
}

}// namespace game
