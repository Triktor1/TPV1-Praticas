#include "Label.h"
#include <SDL3/SDL.h>

Label::Label(GameState* state, SDL_Texture* tex, float x, float y)
    : GameObject(state), texture(tex)
{
    position.x = x;
    position.y = y;

    int w = 0, h = 0;
    position.w = static_cast<float>(w);
    position.h = static_cast<float>(h);

}

void Label::Render() const {
    SDL_RenderTexture(state->getGame()->getRenderer(), texture, nullptr, &position);
}
