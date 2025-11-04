#include "SceneObject.h"
#include <SDL3_image/SDL_image.h>

SceneObject::SceneObject(Point2D<float> position, Texture* texture, Game* game) :
	GameObject(game),
	position(position),
	texture(texture)
{
}

void SceneObject::Render() const {
	SDL_FRect hitbox = getBoundingBox();
	texture->renderFrame(hitbox, 0, 0);
}

void SceneObject::Update() {

}

SDL_FRect SceneObject::getBoundingBox() const{
	return { (float)position.GetX(), (float)position.GetY(), (float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
}

void SceneObject::checkCollision() const{

}
