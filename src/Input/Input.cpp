#include "Input.h"

#include <raylib.h>

namespace game::Input
{
void UpdateButtonState(ButtonState& state, int key)
{
	if (IsKeyPressed(key))
	{
		state = ButtonState::Pressed;
	}
	else if (IsKeyDown(key))
	{
		state = ButtonState::Down;
	}
	else if (IsKeyReleased(key))
	{
		state = ButtonState::Released;
	}
	else if (IsKeyUp(key))
	{
		state = ButtonState::Up;
	}
}

void Init(const flecs::world& ecs)
{
	ecs.component<Input>()
			.member<ButtonState>("thrust")
			.member<ButtonState>("turnRight")
			.member<ButtonState>("turnLeft")
			.member<ButtonState>("hyperJump")
			.member<ButtonState>("shoot");

	ecs.system<Input>("InputSystem")
			.kind(flecs::PostLoad)
			.each([](Input& input) {
				UpdateButtonState(input.thrust, KEY_UP);
				UpdateButtonState(input.turnRight, KEY_RIGHT);
				UpdateButtonState(input.turnLeft, KEY_LEFT);
				UpdateButtonState(input.hyperJump, KEY_DOWN);
				UpdateButtonState(input.shoot, KEY_SPACE);
			});
}

}// namespace game::Input
