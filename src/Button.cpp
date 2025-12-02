#include "Button.h"
#include "GameState.h"
#include <SDL3/SDL.h>

Button::Button(GameState* game, Texture* tex, float x, float y)
    : Label(game,tex,x,y)
{
}

void Button::connect(Callback cb) {
    callbacks.push_back(cb);
}

bool Button::mouseInside(float x, float y) const {
    return x >= position.x && x <= position.x + position.w &&
        y >= position.y && y <= position.y + position.h;
}

void Button::handleEvent(const SDL_Event& e) {
    if (!active) return;
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mx = e.button.x;
        float my = e.button.y;

        if (mouseInside(mx, my)) {
            for (auto& cb : callbacks)
                cb();
        }
    }
    else if (e.type == SDL_EVENT_MOUSE_MOTION) {
        float mx = e.motion.x;
        float my = e.motion.y;

        touched = mouseInside(mx, my);
    }
}

void Button::Render() const {
    if (!active) return;
    if (!touched) {
        Label:: Render();
    }
    else {
        SDL_FRect bigger = position;
        bigger.x -= 2;
        bigger.y -= 2;
        bigger.w += 4;
        bigger.h += 4;

        if (texture)
            texture->render(bigger);
    }
}
