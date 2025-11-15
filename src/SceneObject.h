#pragma once
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"

class SceneObject : public GameObject
{
protected:
	Texture* texture;
	Point2D<float> position;
	SDL_FRect getBoundingBox() const;
public:
	SceneObject(Point2D<float>, Texture*, Game*);
	virtual void Render() const override;
	void Update() override;
	virtual Collision checkCollision(const SDL_FRect&) const;
};
