#include "Label.h"
#include <SDL3/SDL.h>

Label::Label(GameState* game, SDL_Texture* tex, float x, float y)
    : GameObject(game), texture(tex)
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
    SDL_RenderTexture(game->getGame()->getRenderer(), texture, nullptr, &position);
}
