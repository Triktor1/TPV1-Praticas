#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "game.h"
#include "Platform.h"

class Game;
class Collision;

class Log : Platform
{
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> speed;

public:
	Log(Vector2D<float>, Point2D<float>, Texture*, Game*);

	void Render() const;
	void Update();
	Collision CheckCollision(const SDL_FRect& FRect);
};

