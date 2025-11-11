#pragma once
#include "Collision.h"
#include "Crosser.h"

class Vehicle : public Crosser
{
private:

	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> speed;

public:
	Vehicle(Vector2D<float>, Point2D<float>, Texture*, Game*);

	void Update() override;
	Collision CheckCollision(const SDL_FRect& FRect);
};

