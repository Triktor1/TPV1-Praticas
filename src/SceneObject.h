#pragma once
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"

class Game;
class SceneObject : public GameObject
{
protected:
	Game* game;
	Texture* texture;
	Point2D<float> position;

	SDL_FRect getBoundingBox() const;

public:
	SceneObject(Point2D<float>, Texture*, Game*);
	void Render() const override;
	void Update() override;
	void checkCollision() const;
};

