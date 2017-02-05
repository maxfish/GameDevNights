#include "engine/input/include/Keyboard.h"


void Keyboard::beginNewFrame() {
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
}

void Keyboard::keyDownEvent(const SDL_Event &event) {
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

void Keyboard::keyUpEvent(const SDL_Event &event) {
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

bool Keyboard::wasKeyPressed(SDL_Scancode key) {
    return this->_pressedKeys[key];
}

bool Keyboard::wasKeyReleased(SDL_Scancode key) {
    return this->_releasedKeys[key];
}

bool Keyboard::isKeyHeld(SDL_Scancode key) {
    return this->_heldKeys[key];
}