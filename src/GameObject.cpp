#include "GameObject.h"
#include <SDL3_image/SDL_image.h>

GameObject::GameObject(SDLApplication* juego) :
	game(juego)
{
}

GameObject::GameObject(SDLApplication* juego, std::istream& file) :
	game(juego)
{
}

GameObject::~GameObject() {}
