#pragma once
#include "Vector2D.h"
enum Type {
	NONE,
	ENEMY,
	PLATFORM
};

struct Collision {
	Vector2D<int> speed = {0, 0};
	Type tipo = NONE;
};

