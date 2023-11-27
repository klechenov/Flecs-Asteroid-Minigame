#pragma once

#include <raylib.h>

namespace game::Space
{
struct Position final {
	Vector2 val;
};

struct Velocity final {
	Vector2 val;
};

struct Rotation final {
	float val;
};

struct Size final {
	float width;
	float height;
};

}// namespace game::Space
