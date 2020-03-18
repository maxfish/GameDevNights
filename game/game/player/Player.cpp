//
// Created by max on 05/02/17.
//

#include <engine/2d_sprites/spriter/exampleobjectfactory.h>
#include <engine/2d_sprites/spriter/examplefilefactory.h>
#include <entities/Person.h>
#include "Player.h"
#include "Game.h"

Player::Player(Graphics &graphics, World *world, InputController *inputController, int joystick_index) : Person(
        world) {
    _inputController = inputController;
    _joystick_index = joystick_index;

    _direction = DIR_RIGHT;
    _spriter_model = new SpriterEngine::SpriterModel("resources/sprites/Hero/player.scon",
                                                     new SpriterEngine::ExampleFileFactory(graphics.getRenderer()),
                                                     new SpriterEngine::ExampleObjectFactory(graphics.getRenderer())
    );
    _vector_sprite = _spriter_model->getNewEntityInstance("Player");
    if (_vector_sprite) {
        _vector_sprite->setCurrentAnimation("idle");
        _sprite_scale = SpriterEngine::point(SPRITE_SCALE, SPRITE_SCALE);
        _vector_sprite->setScale(_sprite_scale);
        _vector_sprite->setPosition(SpriterEngine::point(_position_x, _position_y));
        _vector_sprite->setAngle(SpriterEngine::toRadians(0));
        _vector_sprite->applyCharacterMap("noArmor");
    }

    addSensor(b2Vec2(-BODY_WIDTH / 2 - 4, 0), b2Vec2(4, 6), SENSOR_ID_WALL_PUSH_LEFT);
    addSensor(b2Vec2(+BODY_WIDTH / 2 + 4, 0), b2Vec2(4, 6), SENSOR_ID_WALL_PUSH_RIGHT);

    _currentState = STATE_STAND = new PlayerStateStand(this);
    STATE_WALK = new PlayerStateWalk(this);
    STATE_JUMP = new PlayerStateJump(this);
    STATE_FALL = new PlayerStateFall(this);
}

void Player::setPosition(float x, float y) {
    Person::setPosition(x, y);
}

void Player::setDirection(int direction) {
    _direction = direction;
    _sprite_scale = SpriterEngine::point(_direction * SPRITE_SCALE, SPRITE_SCALE);
    _vector_sprite->setScale(_sprite_scale);
}

void Player::handleInput(float gameSpeed) {
    Joystick *joystick = _inputController->getJoystickFromIndex(_joystick_index);
    if (!joystick) {
        return;
    }

    _joy_right = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ||
                 joystick->getAxisValue(SDL_CONTROLLER_AXIS_LEFTX) > 0.5;
    _joy_left = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
                joystick->getAxisValue(SDL_CONTROLLER_AXIS_LEFTX) < -0.5;
    _joy_up = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
              joystick->getAxisValue(SDL_CONTROLLER_AXIS_LEFTY) < -0.5;
    _joy_attack = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_A);
    _joy_jump = joystick->isButtonDown(SDL_CONTROLLER_BUTTON_B);

    PlayerState *newState = _currentState->handleInput(gameSpeed);
    if (newState != _currentState) {
        _currentState->leave(newState);
        _currentState->leave(newState);
        newState->enter(_currentState);
        _currentState = newState;
    }
}

void Player::update(float gameSpeed) {
    PlayerState *newState = _currentState->update(gameSpeed);
    if (newState != _currentState) {
        _currentState->leave(newState);
        newState->enter(_currentState);
        _currentState = newState;
    }

    b2Vec2 pos = _world->worldToScreenCoordinates(_body->GetPosition());
    _vector_sprite->setPosition(
            SpriterEngine::point(pos.x + _animation_offset.x, pos.y + BODY_HEIGHT / 2 + _animation_offset.y));
    _vector_sprite->setTimeElapsed(gameSpeed * Game::FRAME_TIME);


//    _vector_sprite->setAngle(3.14-_body->GetAngle());
//    _body->ApplyForceToCenter(b2Vec2(0,+20), true);
//    _person->setPosition(_position_x, _position_y);

//    float32 angle = _body->GetAngle();
//    if (angle > 0.05) {
//        angle = 0.05;
//    } else if (angle < 0.05) {
//        angle = 0.05;
//    }
//    _body->SetTransform(_body->GetPosition(), angle);
}

void Player::draw(Graphics &graphics) {
    _vector_sprite->render();
}

void Player::setAnimation(std::string animationName) {
    _vector_sprite->setCurrentAnimation(animationName);
}

bool Player::onTheGround() {
    int left_foot_contacts = getSensorDataById(SENSOR_ID_FOOT_LEFT)->num_contacts;
    int right_foot_contacts = getSensorDataById(SENSOR_ID_FOOT_RIGHT)->num_contacts;

    return (left_foot_contacts > 0 || right_foot_contacts > 0);
}

// =================================================================================================

void Player::BeginContact(b2Contact *contact) {
}

void Player::EndContact(b2Contact *contact) {
}

void Player::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    // Disable friction when jumping and falling to avoid getting stuck on walls/platforms
    if (contact->GetFixtureA() == _body_fixture || contact->GetFixtureB() == _body_fixture) {
        contact->SetFriction((_currentState == STATE_FALL || _currentState == STATE_JUMP) ? 0 : BODY_FRICTION);
    }
}
