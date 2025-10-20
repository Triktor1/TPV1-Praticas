#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "game.h"

class Game;
class Collision;

class Frog
{
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> lastDir;
	int health = 3;
	int anim;
	double angle;

public:
	Frog(Vector2D<float>, Point2D<float>, int, Texture*, Game*);
	void Render() const;
	void Update();
	void HandleEvent(const SDL_Event&);
};
