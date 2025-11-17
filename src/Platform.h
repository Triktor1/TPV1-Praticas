#pragma once
#include "Crosser.h"

class Platform : public Crosser {
protected:
	using Crosser::Crosser;
public:
	Collision checkCollision(const SDL_FRect& FRect);
};

