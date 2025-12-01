#include "Label.h"
#include <SDL3/SDL.h>
#include "SDLApplication.h"

Label::Label(GameState* game, Texture* tex, float x, float y)
    : GameObject(game), texture(tex)
{
    position.x = x;
    position.y = y;

    int w = 0, h = 0;
    position.w = (float)w;
    position.h = (float)h;

}

void Label::Render() const {
    if (texture)
        texture->render(position);
}

void Label::Update() {
    //Hola update vacío
}
