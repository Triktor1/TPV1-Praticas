#pragma once
#include "Collision.h"
#include "Crosser.h"

class Vehicle : public Crosser
{
public:
	Vehicle(Vector2D<float>, Point2D<float>, Texture*, Game*);
	Vehicle(Game*, std::istream& const);
	Collision checkCollision(const SDL_FRect& FRect) const override;
};
