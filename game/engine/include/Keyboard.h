//
// Created by max on 02/02/17.
//

#pragma once

#include <map>
#include <SDL2/SDL.h>

class Keyboard {

public:
    void beginNewFrame();

    void keyUpEvent(const SDL_Event &event);

    void keyDownEvent(const SDL_Event &event);

    bool wasKeyPressed(SDL_Scancode key);

    bool wasKeyReleased(SDL_Scancode key);

    bool isKeyHeld(SDL_Scancode key);

private:
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releasedKeys;
};
