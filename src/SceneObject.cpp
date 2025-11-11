#include "SceneObject.h"
#include "Game.h"
#include "texture.h"

SceneObject::SceneObject(Point2D<float> position, Texture* texture, Game* game) :
	GameObject(game),
	position(position),
	texture(texture)
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
