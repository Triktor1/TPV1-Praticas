#include "GameObject.h"
#include <SDL3_image/SDL_image.h>

GameObject::GameObject(Game* juego) :
	game(juego)
{
}

GameObject::GameObject(Game* juego, std::istream& file) :
	game(juego)
{
}

GameObject::~GameObject() {}
