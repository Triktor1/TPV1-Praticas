#pragma once
#include "GameObject.h"
#include <SDL3/SDL.h>
class Label: public GameObject
{
protected:
	SDL_Texture* texture;
	SDL_FRect position;

 public:
	Label(GameState* state, SDL_Texture* tex, float x, float y);
	virtual void Render() const override =0;

};

