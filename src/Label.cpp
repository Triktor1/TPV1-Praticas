#include "Label.h"
#include <SDL3/SDL.h>
#include "SDLApplication.h"

Label::Label(GameState* game, Texture* tex, float x, float y)
    : GameObject(game), texture(tex)
{
    position.x = x;
    position.y = y;

    position.w = tex->getFrameWidth();
    position.h = tex->getFrameHeight();

}

void Label::Render() const {
    if (texture)
        texture->render(position);
}

void Label::Update() {
    //Hola update vacío
}
