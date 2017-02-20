//
// Created by max on 05/02/17.
//

#pragma once

#include <engine/2d_sprites/Sprite.h>
#include <engine/entities/Entity.h>
#include <engine/input/Joystick.h>
#include <engine/input/InputController.h>


class Player : public Entity {
    static const int DIR_LEFT = -1;
    static const int DIR_RIGHT = 1;

public:
    Player(Graphics &graphics, InputController *inputController, int joystick_index);

    void handleInput(float game_speed);

    void update(float gameSpeed) override;

    void draw(Graphics &graphics) override;

private:
    int _direction;

    FramesStore *_framesStore;
    Sprite *_sprite;
    float _speed_adjust;

    InputController *_inputController;
    int _joystick_index;
};
