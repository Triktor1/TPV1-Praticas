#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "Collision.h"
#include "game.h"

class Game;
class Collision;

class Wasp
{
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> speed;
	int lifeTime;

public:
	Wasp(Point2D<float>, Vector2D<float>, Texture*, Game*, float);

	void Render() const;
	void Update();
	Collision CheckCollision(const SDL_FRect& FRect);
	bool isAlive() const;
	int getLifeTime() const;
};

