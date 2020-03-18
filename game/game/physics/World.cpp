//
// Created by max on 22/02/17.
//

#include <Box2D/Common/b2Settings.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Draw.h>
#include <engine/core/Graphics.h>
#include "World.h"
#include "physics/SDL2DebugDraw.h"

World::World(Graphics *graphics, float32 width_px, float32 height_px, b2Vec2 gravity) {
    _camera.width = width_px;
    _camera.height = _camera.translation_y = height_px;
    _world = new b2World(gravity);
    _gravity = gravity;

    SDL2DebugDraw *dDraw = new SDL2DebugDraw(graphics->getRenderer(), this);
    dDraw->SetFlags(b2Draw::e_shapeBit);
    _world->SetDebugDraw(dDraw);
}

World::~World() {
    delete (_world);
}

b2World *World::getB2World() {
    return _world;
}

WorldCamera World::getCamera() {
    return _camera;
}

void World::step(float32 timeElapsed) {
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    float accumulator = timeElapsed;
    float stepDuration = 1 / 60;
    while (accumulator > stepDuration) {
        _world->Step(timeElapsed, velocityIterations, positionIterations);
        _world->ClearForces();
        accumulator -= timeElapsed;
    }
}

b2Body *
World::createBox(float32 pos_x, float32 pos_y, float32 half_width, float32 half_height, float32 angle, float32 density, bool dynamic) {
    b2BodyDef body_definition;
    body_definition.type = dynamic ? b2_dynamicBody : b2_staticBody;
    b2Vec2 world_pos = screenToWorldCoordinates(pos_x, pos_y);
    body_definition.position.Set(world_pos.x, world_pos.y);
    body_definition.angle = angle;

    b2Body *_body = _world->CreateBody(&body_definition);
    b2PolygonShape *boxShape = new b2PolygonShape();
    boxShape->SetAsBox(half_width * _camera.anti_scale_factor, half_height * _camera.anti_scale_factor);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = boxShape;
    fixtureDef.density = density;
    fixtureDef.friction = 0.2;
    _body->CreateFixture(&fixtureDef);
    return _body;
}

b2Body *World::createEdge(b2Vec2 from, b2Vec2 to) {
    b2BodyDef bd;
    b2Body *edge = _world->CreateBody(&bd);
    b2EdgeShape shape;
    shape.Set(screenToWorldCoordinates(from), screenToWorldCoordinates(to));
    edge->CreateFixture(&shape, 0);
    return edge;
}

void World::debugDraw() {
    _world->DrawDebugData();
}

b2Vec2 World::worldToScreenCoordinates(b2Vec2 world) {
    float x = map_coords(world.x, 0.0f, 1.0f, _camera.translation_x, _camera.translation_x + _camera.scale_factor);
    float y = map_coords(world.y, 0.0f, 1.0f, _camera.translation_y, _camera.translation_y + _camera.scale_factor);
    if (_camera.vertical_flip) {
        y = map_coords(y, 0.0f, _camera.height, _camera.height, 0.0f);
    }
    return b2Vec2(x, y);
}

b2Vec2 World::worldToScreenCoordinates(float x, float y) {
    return worldToScreenCoordinates(b2Vec2(x, y));
}

b2Vec2 World::screenToWorldCoordinates(b2Vec2 screen) {
    return screenToWorldCoordinates(screen.x, screen.y);
}

b2Vec2 World::screenToWorldCoordinates(float screenX, float screenY) {
    float x = map_coords(screenX + _camera.offset_x, _camera.translation_x,
                         _camera.translation_x + _camera.scale_factor, 0.0f, 1.0f);
    float y = screenY + _camera.offset_y;
    if (_camera.vertical_flip) {
        y = map_coords(y, _camera.height, 0.0f, 0.0f, _camera.height);
    }
    y = map_coords(y, _camera.translation_y, _camera.translation_y + _camera.scale_factor, 0.0f, 1.0f);

    return b2Vec2(x, y);
}

#pragma -------------------------------------------------------------------------------------

float World::map_coords(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
