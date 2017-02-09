//
// Created by max on 05/02/17.
//

#include <globals.h>
#include "Player.h"

Player::Player(Graphics &graphics, InputController *inputController, int joystick_index) {
    Entity();

    _framesStore = new FramesStore(graphics);
    _framesStore->load("resources/sprites/cody", "sprites.json");

    _inputController = inputController;
    _joystick_index = joystick_index;

    _sprite = new Sprite(_framesStore);
    _sprite->playAnimation("walk", Sprite::FLAG_LOOP_ANIMATION);
    _sprite->setPosition(140,120);
}

void Player::handleInput(float game_speed) {
    Joystick *j = _inputController->getJoystickFromIndex(_joystick_index);
    if (!j) {
        return;
    }
    if(j->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        _position.x += 5 * game_speed;
    }
}

void Player::update(float gameSpeed) {
    _sprite->setPosition(_position.x, _position.y);
    _sprite->update(gameSpeed);
}

void Player::draw(Graphics &graphics) {
    _sprite->draw(graphics);
}

