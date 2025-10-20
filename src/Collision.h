#pragma once
#include "Vector2D.h"
enum Type {
	NONE,
	ENEMY,
	PLATFORM,
	HOME
};

struct Collision {
	Vector2D<float> speed = {0, 0};
	Type tipo = NONE;
};

