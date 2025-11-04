#include "GameObject.h"
#include <SDL3_image/SDL_image.h>

void GameObject::Render() const{

}

void GameObject::Update() {

}

GameObject::GameObject(Game* juego) :
	game(juego)
{
}

GameObject::~GameObject() {
	delete game;
}
