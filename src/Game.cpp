#include "Game.h"

#include <raylib.h>

#include "Rendering/Renderer.h"

namespace game
{

Game::Game()
{
	mEcs.set<flecs::Rest>({});
	flecs::log::set_level(0);
	mEcs.import<flecs::monitor>();

	game::Rendering::Init(mEcs);
}

void Game::Start()
{
	while (mEcs.progress(GetFrameTime()))
	{
		if (WindowShouldClose())
			mEcs.quit();
	}
}

} // namespace game