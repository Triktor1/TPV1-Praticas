#include "Label.h"
#include <SDL3/SDL.h>

Label::Label(GameState* state, SDL_Texture* tex, float x, float y):
    GameObject(state->getGame())
{
    state = state; 
    texture = tex; 
    position.x = x;
    position.y = y;

    int w = 0, h = 0;
    position.w = (float)w;
    position.h = (float)h;

}

void Label::Render() const {
    SDL_RenderTexture(state->getGame()->getRenderer(), texture, nullptr, &position);
}
