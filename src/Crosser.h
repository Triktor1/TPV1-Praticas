#pragma once
#include "SceneObject.h"

class Crosser : public SceneObject
{
private:

	Point2D<float> position;
	Vector2D<float> speed;
	int backjump;

public:
	Crosser(Point2D<float> position, Vector2D<float> speed, Texture* texture, Game* game);
	void Update();
	Vector2D<float> getSpeed() const;
	virtual Collision checkCollision(const SDL_FRect& FRect) const override;

};
