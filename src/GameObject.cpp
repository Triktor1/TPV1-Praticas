#include "GameObject.h"
#include "GameState.h"
#include <SDL3_image/SDL_image.h>

GameObject::GameObject(GameState* game) :
	game(game)
{
}

GameObject::GameObject(GameState* game, std::istream& file) :
	game(game)
{
}
