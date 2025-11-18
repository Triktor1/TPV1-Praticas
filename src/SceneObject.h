#pragma once
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "Collision.h"

class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	Texture* texture;
	SDL_FRect getBoundingBox() const;
public:
	SceneObject(Point2D<float>, Texture*, Game*);
	SceneObject(Game*, std::istream&);
	virtual void Render() const override;
	void Update() override;
	virtual Collision checkCollision(const SDL_FRect&) const;
};
