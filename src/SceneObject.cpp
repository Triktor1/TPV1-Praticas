#include "SceneObject.h"
#include <SDL3_image/SDL_image.h>

SceneObject::SceneObject() {

}

void SceneObject::Render() const {
	SDL_FRect hitbox = { (float)position.GetX(), (float)position.GetY(),
		(float)texture->getFrameWidth(), (float)texture->getFrameHeight() };
	texture->renderFrame(hitbox, 0, 0);
}

void SceneObject::Update() {

}
