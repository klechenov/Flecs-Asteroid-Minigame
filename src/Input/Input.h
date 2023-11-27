#pragma once

#include <flecs.h>

namespace game::Input
{
enum class ButtonState
{
	Up = 0,
	Pressed,
	Down,
	Released
};

struct Input final {
	ButtonState thrust = ButtonState::Up;
	ButtonState turnRight = ButtonState::Up;
	ButtonState turnLeft = ButtonState::Up;
	ButtonState hyperJump = ButtonState::Up;
	ButtonState shoot = ButtonState::Up;
};

void Init(const flecs::world& ecs);
void UpdateButtonState(ButtonState& state, int key);

}// namespace game::Input
