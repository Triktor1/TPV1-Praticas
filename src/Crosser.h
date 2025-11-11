#pragma once
#include "SceneObject.h"

class Crosser : public SceneObject
{
private:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> speed;

public:
	Crosser(Point2D<float> position, Vector2D<float> speed, Texture* texture, Game* game);
	void Update();
	Vector2D<float> getSpeed() const;
};
