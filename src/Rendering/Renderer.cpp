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

void InitRender(const flecs::world& ecs)
{
	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(FPS);

	rlImGuiSetup(true);

	ecs.component<VisualComponent>("VisualComponent")
			.member<int>("zOrder");
}

void InitSystems(const flecs::world& ecs)
{
	ecs.system("Renderer::PreDraw")
			.kind(flecs::PreStore)
			.each(PreDraw);

	//TODO: Waiting what Sander says about order_by PR
	ecs.system<const VisualComponent, const Space::PositionComponent, const Space::SizeComponent, const Space::RotationComponent>("Renderer::DrawEntities")
			.kind(flecs::PreStore)
			.with<Rocket::RocketTag>()
			.oper(flecs::Or)
			.with<Ship::ShipTag>()
			.oper(flecs::Or)
			.with<Asteroid::AsteroidTag>()
			.order_by<const VisualComponent>(
					[](flecs::entity_t e1, const VisualComponent* p1,
					   flecs::entity_t e2, const VisualComponent* p2) {
							return (p1->zOrder > p2->zOrder) - (p1->zOrder < p2->zOrder);
					})
			.each([](flecs::entity entity, const VisualComponent& visual, const Space::PositionComponent& pos, const Space::SizeComponent& size, const Space::RotationComponent& rot) {
				const Rectangle sourceRec = {0, 0, static_cast<float>(visual.texture.width), static_cast<float>(visual.texture.height)};
				const Rectangle destRec = {pos.val.x, pos.val.y, static_cast<float>(size.width), static_cast<float>(size.height)};
				const Vector2 origin = {static_cast<float>(size.width) * .5f, static_cast<float>(size.height) * .5f};

				DrawTexturePro(visual.texture, sourceRec, destRec, origin, rot.val, WHITE);

				// Debugging stuff
				//DrawCircle(pos.val.x, pos.val.y, 10, BLUE);
				//DrawRectangleLines(destRec.x - size.width * .5f, destRec.y - size.height * .5f, destRec.width, destRec.height, RED);
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
