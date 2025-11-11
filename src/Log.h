#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Platform.h"
#include "game.h"

class Collision;

class Log : Platform
{
	using Platform::Platform;
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> speed;

public:

	void Render() const;
	void Update();
	Collision CheckCollision(const SDL_FRect& FRect);
};

