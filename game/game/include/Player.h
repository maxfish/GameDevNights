//
// Created by max on 05/02/17.
//

#pragma once

#include <engine/2d_sprites/include/Sprite.h>
#include <engine/entities/include/Entity.h>
#include <engine/input/include/Joystick.h>
#include <engine/input/include/InputController.h>

class Player : public Entity {
public:
    Player(Graphics &graphics, InputController *inputController, int joystick_index);

    void handleInput(float game_speed);

    void update(float gameSpeed) override;

    void draw(Graphics &graphics) override;

private:
    FramesStore *_framesStore;
    Sprite *_sprite;
    InputController *_inputController;
    int _joystick_index;
};
