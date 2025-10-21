#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "game.h"

class Game;

class HomedFrog
{
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	bool reached;
public:

	HomedFrog(Point2D<float>, Texture*, Game*);
	void Render() const;
	Collision CheckCollision(const SDL_FRect& FRect);
	void SetReached(bool hasReached);
	bool GetReached() const;
};
