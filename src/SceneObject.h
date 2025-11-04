#pragma once
#include "GameObject.h"

class SceneObject : public GameObject
{
protected:
	Game* game;
	Texture* texture;
	Point2D<float> position;
	Vector2D<float> speed;

public:
	SceneObject();
	void Render() const override;
	void Update() override;
};

