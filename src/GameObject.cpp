#include "GameObject.h"
#include <SDL3_image/SDL_image.h>

GameObject::GameObject(Game* juego) :
	game(juego)
{
}

GameObject::~GameObject() {
	delete game;
}
