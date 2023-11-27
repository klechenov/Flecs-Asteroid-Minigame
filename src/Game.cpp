#include "Game.h"

#include <raylib.h>

#include "Asteroid/Asteroid.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "Rocket/Rocket.h"
#include "Ship/Ship.h"
#include "Space/Space.h"

namespace game
{
void Init(const flecs::world& ecs)
{
	ecs.system<const game::Space::Size, game::Space::Position>("OffScreenSystem")
			.kind(flecs::PreUpdate)
			.term<game::Rocket::Rocket>()
			.oper(flecs::Or)
			.term<game::Asteroid::Asteroid>()
			.oper(flecs::Or)
			.term<game::Ship::Ship>()
			.each([](flecs::entity e, const game::Space::Size& size, game::Space::Position& pos) {
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

				if (e.has<game::Rocket::Rocket>())
				{
					e.destruct();
				}
				else if ((e.has<game::Asteroid::Asteroid>() || e.has<game::Ship::Ship>()))
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

	game::Input::Init(mEcs);
	game::Rendering::Init(mEcs);
	game::Init(mEcs);
	game::Ship::Init(mEcs);
	game::Rocket::Init(mEcs);
	game::Asteroid::Init(mEcs);
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
