#pragma once

#include "Platform.h"

class Log : public Platform
{
	using Platform::Platform;
public:
	Log(Vector2D<float>, Point2D<float>, Texture*, SDLApplication*);
	Log(SDLApplication*, std::istream&);
	Collision checkCollision(const SDL_FRect& FRect) const override;
};
