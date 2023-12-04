#include "Ship.h"

#include "Asteroid/Asteroid.h"
#include "Collision/Collision.h"
#include "Globals.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "Rocket/Rocket.h"
#include "Space/Space.h"

#include <cmath>
#include <raylib.h>

namespace game::Ship
{
using InputComponent = Input::InputComponent;
using ButtonState = Input::ButtonState;
using VelocityComponent = Space::VelocityComponent;
using PositionComponent = Space::PositionComponent;
using RotationComponent = Space::RotationComponent;
using Size = Space::SizeComponent;
using VisualComponent = Rendering::VisualComponent;

void Init(const flecs::world& ecs)
{
	const Vector2 shipPosition = {GetScreenWidth() * .5f, GetScreenHeight() * .5f};
	ecs.entity("Ship")
			.add<ShipTag>()
			.add<Collision::CollisionRelationship, Asteroid::AsteroidTag>()
			.emplace<InputComponent>()
			.emplace<VisualComponent>(1, LoadTexture("res/ship.png"))
			.emplace<VelocityComponent>(0.f, 0.f)
			.emplace<PositionComponent>(shipPosition)
			.emplace<RotationComponent>(0.f)
			.emplace<Size>(SHIP_WIDTH, SHIP_HEIGHT);

	ecs.system<const InputComponent, PositionComponent, VelocityComponent, RotationComponent>("ShipInputHandler")
			.kind(flecs::OnUpdate)
			.each([&ecs](const InputComponent& input, PositionComponent& pos, VelocityComponent& vel, RotationComponent& rot) {
				if (input.shoot == ButtonState::Pressed)
				{
					Rocket::FireRocket(ecs, pos.val, rot.val);
				}

				const float deltaTime = GetFrameTime();

				if (input.turnRight == ButtonState::Down)
				{
					rot.val += SHIP_ROTATION_SPEED * deltaTime;
				}
				if (input.turnLeft == ButtonState::Down)
				{
					rot.val -= SHIP_ROTATION_SPEED * deltaTime;
				}
				rot.val = std::fmod(rot.val, 360.0f);

				if (input.thrust == ButtonState::Down)
				{
					const float rad = rot.val * DEG2RAD;

					vel.val.x += std::sin(rad) * SHIP_ACCELERATION * deltaTime;
					vel.val.y -= std::cos(rad) * SHIP_ACCELERATION * deltaTime;
				}

				// Apply space friction
				vel.val.x *= std::pow(1 - SPACE_FRICTION, deltaTime);
				vel.val.y *= std::pow(1 - SPACE_FRICTION, deltaTime);

				pos.val.x += vel.val.x * deltaTime;
				pos.val.y += vel.val.y * deltaTime;

				// Debugging stuff
				DrawText(TextFormat("Position: (%.2f, %.2f)", pos.val.x, pos.val.y), 10, 10, 20, RED);
				DrawText(TextFormat("Velocity: (%.2f, %.2f)", vel.val.x, vel.val.y), 10, 30, 20, RED);
				DrawText(TextFormat("Rotation: %.2f", rot.val), 10, 50, 20, RED);
			});
}

}// namespace game::Ship
