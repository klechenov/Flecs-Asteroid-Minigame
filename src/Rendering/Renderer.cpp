#include "Renderer.h"

#include <raylib.h>
#include <rlImGui.h>

#include "Asteroid/Asteroid.h"
#include "DebugWindow.h"
#include "Globals.h"
#include "Rocket/Rocket.h"
#include "Ship/Ship.h"
#include "Space/Space.h"

#include <cmath>

namespace game::Rendering
{

static void PreDraw(const flecs::iter& iter, int index);
static void DrawDebug(const flecs::iter& iter, int index);
static void PostDraw(const flecs::iter& iter, int index);

void Init(const flecs::world& ecs)
{
	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(FPS);

	rlImGuiSetup(true);

	ecs.system("Renderer::PreDraw")
			.kind(flecs::PreStore)
			.each(PreDraw);

	ecs.system<const game::Rocket::Rocket, const game::Space::Velocity, const game::Space::Position, const Visual, const game::Space::Size>("Renderer::DrawRocket")
			.kind(flecs::PreStore)
			.each([](const game::Rocket::Rocket&, const game::Space::Velocity& vel, const game::Space::Position& pos, const Visual& visual, const game::Space::Size& size) {
				const float rotationAngle = atan2(vel.val.x, -vel.val.y) * RAD2DEG;
				const Rectangle sourceRec = {0, 0, static_cast<float>(visual.texture.width), static_cast<float>(visual.texture.height)};
				const Rectangle destRec = {pos.val.x, pos.val.y, size.width, size.height};
				const Vector2 origin = {size.width * .5f, size.height * .5f};

				DrawTexturePro(visual.texture, sourceRec, destRec, origin, rotationAngle, WHITE);

				// Debugging stuff
				/*DrawCircle(pos.val.x, pos.val.y, 10, BLUE);
				DrawRectangleLines(destRec.x - size.width * .5f, destRec.y - size.height * .5f, destRec.width, destRec.height, RED);*/
			});

	ecs.system<const game::Ship::Ship, const game::Space::Position, const game::Space::Rotation, const game::Space::Size, const Visual>("Renderer::DrawShip")
			.kind(flecs::PreStore)
			.each([](const game::Ship::Ship&, const game::Space::Position& pos, const game::Space::Rotation& rot, const game::Space::Size& size, const Visual& visual) {
				const Rectangle sourceRec = {0, 0, static_cast<float>(visual.texture.width), static_cast<float>(visual.texture.height)};
				const Rectangle destRec = {pos.val.x, pos.val.y, size.width, size.height};
				const Vector2 origin = {size.width * .5f, size.height * .5f};

				DrawTexturePro(visual.texture, sourceRec, destRec, origin, rot.val, WHITE);

				// Debugging stuff
				/*DrawCircle(pos.val.x, pos.val.y, 10, BLUE);
				DrawRectangleLines(destRec.x - size.width * .5f, destRec.y - size.height * .5f, destRec.width, destRec.height, RED);*/
			});

	ecs.system<const game::Asteroid::Asteroid, const game::Space::Position, const Visual, const game::Space::Size>("DrawRocket::DrawAsteroid")
			.kind(flecs::PreStore)
			.each([](const game::Asteroid::Asteroid&, const game::Space::Position& pos, const Visual& visual, const game::Space::Size& size) {
				const Rectangle sourceRec = {0, 0, static_cast<float>(visual.texture.width), static_cast<float>(visual.texture.height)};
				const Rectangle destRec = {pos.val.x, pos.val.y, size.width, size.height};
				const Vector2 origin = {size.width * .5f, size.height * .5f};

				DrawTexturePro(visual.texture, sourceRec, destRec, origin, 0.f, WHITE);

				// Debugging stuff
				/*DrawCircle(pos.val.x, pos.val.y, 10, BLUE);
				DrawRectangleLines(destRec.x - size.width * .5f, destRec.y - size.height * .5f, destRec.width, destRec.height, RED);*/
			});

	ecs.system("Renderer::DrawDebug")
			.kind(flecs::PreStore)
			.each(DrawDebug);

	ecs.system("Renderer::PostDraw")
			.kind(flecs::PreStore)
			.each(PostDraw);
}

void PreDraw(const flecs::iter& iter, int index)
{
	BeginDrawing();
	rlImGuiBegin();

	ClearBackground(BLACK);
}

void DrawDebug(const flecs::iter& iter, int index)
{
	DrawFPS(0, 0);

	//flecs::world ecs = iter.world();

	//DrawDebugWindow();
	// Keeping this commented to have it at hand easily when we need to look at the demo window.
	// ImGui::ShowDemoWindow();
}

void PostDraw(const flecs::iter& iter, int index)
{
	rlImGuiEnd();
	EndDrawing();
}

}// namespace game::Rendering
