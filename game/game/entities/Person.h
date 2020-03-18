//
// Created by max on 03/03/17.
//

#pragma once

#include <engine/entities/Entity.h>
#include <Box2D/Box2D.h>
#include <physics/World.h>
#include <physics/FixtureUserData.h>

class Person : public Entity, public b2ContactListener {
public:
    constexpr static const int SENSOR_ID_FOOT_LEFT = 1;
    constexpr static const int SENSOR_ID_FOOT_RIGHT = 2;

    constexpr static const float BODY_WIDTH = 32;
    constexpr static const float BODY_HEIGHT = 74;
    constexpr static const float BODY_FRICTION = 0.4;

    Person(World *world);

    void setPosition(float x, float y) override;

    b2Body *getBody() const;

    b2Fixture *getSensorById(int id);

    FixtureUserData *getSensorDataById(int id);

protected:
    World *_world;
    b2Body *_body;
    b2Fixture *_body_fixture;
    std::map<int, b2Fixture*> *_sensors;

    void initBody();

    b2Fixture *addSensor(b2Vec2 pos, b2Vec2 size, int id);
};
