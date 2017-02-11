//
// Created by max on 05/02/17.
//

#include <globals.h>
#include "Player.h"

static const int WALK_SPEED = 2;

Player::Player(Graphics &graphics, InputController *inputController, int joystick_index) {
    Entity();

    _framesStore = new FramesStore(graphics);
    _framesStore->load("resources/sprites/cody", "sprites.json");

    _inputController = inputController;
    _joystick_index = joystick_index;

    _sprite = new Sprite(_framesStore);
    _sprite->playAnimation("stand", 0);

    _direction = DIR_RIGHT;
}

void Player::handleInput(float game_speed) {
    Joystick *joystick = _inputController->getJoystickFromIndex(_joystick_index);
    if (!joystick) {
        return;
    }

    bool joy_right = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || joystick->getAxisValue(SDL_CONTROLLER_AXIS_LEFTX) > 0.5;
    bool joy_left = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT) || joystick->getAxisValue(SDL_CONTROLLER_AXIS_LEFTX) < -0.5;

    if (joy_left) {
        _direction = DIR_LEFT;
    } else if (joy_right) {
        _direction = DIR_RIGHT;
    }

    Uint16 flags = (Uint16) (Sprite::FLAG_LOOP_ANIMATION | (_direction == DIR_LEFT ? Sprite::FLAG_FLIP_X : 0));

    if(joy_right) {
        _position_x += WALK_SPEED * game_speed;
        _sprite->playAnimation("walk", flags);
    } else if(joy_left) {
        _position_x -= WALK_SPEED * game_speed;
        _sprite->playAnimation("walk", flags);
    } else {
        _sprite->playAnimation("stand", flags);
    }
}

void Player::update(float gameSpeed) {
    _sprite->setPosition((int) _position_x, (int) _position_y);
    _sprite->update(gameSpeed);
}

void Player::draw(Graphics &graphics) {
    _sprite->draw(graphics);
}

