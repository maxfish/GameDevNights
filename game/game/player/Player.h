//
// Created by max on 05/02/17.
//

#pragma once

#include <engine/2d_sprites/bitmap/Sprite.h>
#include <engine/entities/Entity.h>
#include <engine/input/Joystick.h>
#include <engine/input/InputController.h>
#include <spriterengine/spriterengine.h>
#include "entities/Person.h"
#include "physics/World.h"
#include "PlayerStates.h"

class Player : public Person {
    constexpr static const int SENSOR_ID_WALL_PUSH_LEFT = 10;
    constexpr static const int SENSOR_ID_WALL_PUSH_RIGHT = 11;

    constexpr static const int DIR_LEFT = -1;
    constexpr static const int DIR_RIGHT = 1;
    constexpr static const float SPRITE_SCALE = 0.3f;

public:
    Player(Graphics &graphics, World *world, InputController *inputController, int joystick_index);

    void handleInput(float gameSpeed);

    void update(float gameSpeed) override;

    void draw(Graphics &graphics) override;

    void setPosition(float x, float y) override;

    void setDirection(int direction);

    void setAnimation(std::string animationName);

    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

private:
    PlayerState *STATE_STAND;
    PlayerState *STATE_WALK;
    PlayerState *STATE_JUMP;
    PlayerState *STATE_FALL;

    friend class PlayerState;

    friend class PlayerStateStand;

    friend class PlayerStateWalk;

    friend class PlayerStateJump;

    friend class PlayerStateFall;

    PlayerState *_currentState;
    int _direction;

    InputController *_inputController;
    int _joystick_index;
    bool _joy_up, _joy_down, _joy_left, _joy_right, _joy_attack, _joy_jump;

    SpriterEngine::SpriterModel *_spriter_model;
    SpriterEngine::EntityInstance *_vector_sprite;
    SpriterEngine::point _sprite_scale;
    b2Vec2 _animation_offset;

    bool onTheGround();
};

