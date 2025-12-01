#pragma once
#include "Label.h"
#include "EventHandler.h"
#include <vector>
#include <functional>

class Button : public Label, public EventHandler {
public:
    using Callback = std::function<void()>;
    Button(GameState* game, Texture* tex, float x, float y);

    // Registrar una acción
    void connect(Callback cb);

    virtual void handleEvent(const SDL_Event& e) override;
    virtual void Render() const override;

private:
    bool mouseInside(float x, float y) const;
    bool touched = false;
    std::vector<Callback> callbacks;
};




