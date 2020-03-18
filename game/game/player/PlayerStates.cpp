//
// Created by max on 05/03/17.
//

#include "Player.h"
#include "PlayerStates.h"

void PlayerState::handleInputInAir(float gameSpeed) {
    b2Vec2 v = _p->getBody()->GetLinearVelocity();
    if (_p->_joy_right) {
        v.x = SPEED_IN_AIR_H;
        _p->setDirection(_p->DIR_RIGHT);
        _p->getBody()->SetLinearVelocity(v);
    } else if (_p->_joy_left) {
        v.x = -SPEED_IN_AIR_H;
        _p->setDirection(_p->DIR_LEFT);
        _p->getBody()->SetLinearVelocity(v);
    }
}

bool PlayerState::hasToFall() {
    return !_p->onTheGround();
}

// =========================================================================================

void PlayerStateStand::enter(PlayerState *oldState) {
    _p->setAnimation("idle");
}

void PlayerStateStand::leave(PlayerState *newState) {
    PlayerState::leave(newState);
}

PlayerState *PlayerStateStand::handleInput(float gameSpeed) {
    PlayerState::handleInput(gameSpeed);

    if (_p->_joy_jump) {
        return _p->STATE_JUMP;
    }

    if (_p->_joy_right || _p->_joy_left) {
        return _p->STATE_WALK;
    }

    return this;
}

PlayerState *PlayerStateStand::update(float gameSpeed) {
    PlayerState::update(gameSpeed);

    if (!_p->onTheGround()) {
        return _p->STATE_FALL;
    }

    int ground_sensor_id = _p->_direction == _p->DIR_LEFT ? _p->SENSOR_ID_FOOT_LEFT : _p->SENSOR_ID_FOOT_RIGHT;
    int other_ground_sensor_id = _p->_direction == _p->DIR_LEFT ? _p->SENSOR_ID_FOOT_RIGHT : _p->SENSOR_ID_FOOT_LEFT;
    if (_p->getSensorDataById(ground_sensor_id)->num_contacts == 0 &&
        _p->getSensorDataById(other_ground_sensor_id)->num_contacts > 0) {
        _p->setAnimation("balance_check");
    } else {
        _p->setAnimation("idle");
    }

    return this;
}

// =========================================================================================

void PlayerStateWalk::enter(PlayerState *oldState) {
    _p->setAnimation("walk");
}

void PlayerStateWalk::leave(PlayerState *newState) {
    PlayerState::leave(newState);
    _p->_animation_offset.x = 0;
}

PlayerState *PlayerStateWalk::handleInput(float gameSpeed) {
    PlayerState::handleInput(gameSpeed);

    if (!_pushing && _p->_joy_jump && _p->onTheGround()) {
        return _p->STATE_JUMP;
    }

    if (!_p->_joy_right && !_p->_joy_left) {
        return _p->STATE_STAND;
    }

    // Pushing blocks/walls
    int push_sensor_id = _p->_direction == _p->DIR_LEFT ? _p->SENSOR_ID_WALL_PUSH_LEFT : _p->SENSOR_ID_WALL_PUSH_RIGHT;
    if (_p->getSensorDataById(push_sensor_id)->num_contacts > 0) {
        _p->setAnimation("push_block");
        _p->_animation_offset.x = -18 * _p->_direction;
        _pushing = true;
    } else {
        _p->setAnimation("walk");
        _p->_animation_offset.x = 0;
        _pushing = false;
    }

    b2Vec2 v = _p->getBody()->GetLinearVelocity();
    if (_p->_joy_right) {
        v.x = _pushing ? SPEED_PUSH : SPEED_WALK;
        _p->setDirection(_p->DIR_RIGHT);
        _p->getBody()->SetLinearVelocity(v);
    } else if (_p->_joy_left) {
        v.x = -(_pushing ? SPEED_PUSH : SPEED_WALK);
        _p->setDirection(_p->DIR_LEFT);
        _p->getBody()->SetLinearVelocity(v);
    }

    return this;
}

PlayerState *PlayerStateWalk::update(float gameSpeed) {
    PlayerState::update(gameSpeed);

    if (hasToFall()) {
        // TODO: When friction is != 0, the player remain stuck and doesn't fall
        return _p->STATE_FALL;
    }

    return this;
}

// =========================================================================================

void PlayerStateJump::enter(PlayerState *oldState) {
//    _p->setFrictionEnabled(false);

    if (_p->_joy_right) {
        _p->setDirection(_p->DIR_RIGHT);
    } else if (_p->_joy_left) {
        _p->setDirection(_p->DIR_LEFT);
    }

    float h_impulse = 0;
    if (_p->_joy_left || _p->_joy_right) {
        h_impulse = _p->_direction * IMPULSE_JUMP_H;
    }
    _p->getBody()->ApplyLinearImpulse(b2Vec2(h_impulse, IMPULSE_JUMP_V), b2Vec2(0, 0), true);
    _p->_vector_sprite->setCurrentAnimation("jump_loop");
}

void PlayerStateJump::leave(PlayerState *newState) {
    PlayerState::leave(newState);
//    _p->setFrictionEnabled(true);
}

PlayerState *PlayerStateJump::handleInput(float gameSpeed) {
    PlayerState::handleInput(gameSpeed);

    if (_p->_joy_right) {
        _p->setDirection(_p->DIR_RIGHT);
    } else if (_p->_joy_left) {
        _p->setDirection(_p->DIR_LEFT);
    }

    return this;
}

PlayerState *PlayerStateJump::update(float gameSpeed) {
    PlayerState::update(gameSpeed);

    handleInputInAir(gameSpeed);

    if (_p->getBody()->GetLinearVelocity().y <= 0) {
        return _p->STATE_FALL;
    }
    return this;
}

// =========================================================================================

void PlayerStateFall::enter(PlayerState *oldState) {
//    _p->setFrictionEnabled(false);
    _p->_vector_sprite->setCurrentAnimation("fall_loop");
}

void PlayerStateFall::leave(PlayerState *newState) {
    PlayerState::leave(newState);
//    _p->setFrictionEnabled(true);
}

PlayerState *PlayerStateFall::handleInput(float gameSpeed) {
    PlayerState::handleInput(gameSpeed);
    handleInputInAir(gameSpeed);
    return this;
}

PlayerState *PlayerStateFall::update(float gameSpeed) {
    PlayerState::update(gameSpeed);
    if (_p->onTheGround()) {
        return _p->STATE_STAND;
    }

    return this;
}

