#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Platform.h"
#include "game.h"

class Collision;

class Log : public Platform
{
	using Platform::Platform;
public:
	Log(Vector2D<float>, Point2D<float>, Texture*, Game*);
	Log(Game*, std::istream& const);
	void Render() const;
	void Update();
	Collision checkCollision(const SDL_FRect& FRect) const override;
};
