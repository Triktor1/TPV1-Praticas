#pragma once
#include "Crosser.h"
#include "Collision.h"

class Platform : public Crosser {
	using Crosser::Crosser;

public:
	Collision checkCollision(const SDL_FRect& FRect);
};

