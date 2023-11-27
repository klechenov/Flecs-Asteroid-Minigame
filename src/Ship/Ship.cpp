#include "Ship.h"

#include "Globals.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "Rocket/Rocket.h"
#include "Space/Space.h"

#include <cmath>
#include <raylib.h>

namespace game::Ship
{
using Input = game::Input::Input;
using ButtonState = game::Input::ButtonState;
using Velocity = game::Space::Velocity;
using Position = game::Space::Position;
using Rotation = game::Space::Rotation;
using Size = game::Space::Size;
using Visual = game::Rendering::Visual;

void Init(const flecs::world& ecs)
{
	ecs.entity("Ship")
			.add<Ship>()
			.add<Input>()
			.set<Visual>({LoadTexture("res/ship.png")})
			.set<Velocity>({0, 0})
			.set<Position>({{GetScreenWidth() * .5f, GetScreenHeight() * .5f}})
			.set<Rotation>({0})
			.set<Size>({SHIP_WIDTH, SHIP_HEIGHT});

	ecs.system<const Input, Position, Velocity, Rotation>("ShipInputHandler")
			.kind(flecs::OnUpdate)
			.each([&ecs](const Input& input, Position& pos, Velocity& vel, Rotation& rot) {
				if (input.shoot == ButtonState::Pressed)
				{
					// TODO: Creating new entities every frame can be costly if not managed properly.
					// Implement a pooling system or limit the number of active rockets if needed.
					game::Rocket::FireRocket(ecs, pos.val, rot.val);
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
