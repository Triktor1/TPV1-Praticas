#include "SceneObject.h"

SceneObject::SceneObject(Point2D<float> position, Texture* texture, Game* game) :
	GameObject(game),
	position(position),
	texture(texture)
{
	height = texture->getFrameHeight();
	width = texture->getFrameWidth();
}

SceneObject::SceneObject(Game* game, std::istream& file) :
	GameObject(game, file)
{
}

void SceneObject::Render() const {
	texture->renderFrame(getBoundingBox(), 0, 0);
}

void SceneObject::Update() {

}

SDL_FRect SceneObject::getBoundingBox() const{
	return { (float)position.GetX(), (float)position.GetY(), (float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
}

Collision SceneObject::checkCollision(const SDL_FRect&) const {
	Collision collision;
	collision.tipo = NONE;
	collision.speed = Vector2D<float>(0, 0);
	return collision;
}
