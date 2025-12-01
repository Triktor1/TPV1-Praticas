#pragma once
#include "GameObject.h"
#include <SDL3/SDL.h>
#include "texture.h"

class Label: public GameObject
{
protected:
	Texture* texture;
	SDL_FRect position;

 public:
	Label(GameState* game, Texture* tex, float x, float y);
	virtual void Render() const override;
	virtual void Update() override;

};
