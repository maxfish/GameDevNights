//
// Created by max on 03/03/17.
//

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Game.h>

Person::Person(World *world) : _world(world)    {
    _sensors = new std::map<int, b2Fixture *>();
    initBody();
}

void Person::initBody() {
    b2BodyDef body_definition;
    body_definition.type = b2_dynamicBody;
    b2Vec2 wp = _world->screenToWorldCoordinates(_position_x, _position_y);
    body_definition.position.Set(wp.x, wp.y);
    body_definition.angle = 0;
    body_definition.linearDamping = 0.6;
    body_definition.fixedRotation = true;
    body_definition.userData = this;
    _body = _world->getB2World()->CreateBody(&body_definition);
    _body->SetBullet(true);

    float32 w = BODY_WIDTH * _world->getCamera().anti_scale_factor;
    float32 h = BODY_HEIGHT * _world->getCamera().anti_scale_factor;

    b2PolygonShape *polygonShape = new b2PolygonShape();
    b2Vec2 points[7];
    points[0] = b2Vec2(0, h * 0.5f);
    points[1] = b2Vec2(-w * 0.5f, h * 0.5f - w * 0.5f);
    points[2] = b2Vec2(-w * 0.5f, -h * 0.5f + w * 0.3f);
    points[3] = b2Vec2(-w * 0.25f, -h * 0.5f);
    points[4] = b2Vec2(w * 0.25f, -h * 0.5f);
    points[5] = b2Vec2(w * 0.5f, -h * 0.5f + w * 0.3f);
    points[6] = b2Vec2(w * 0.5f, h * 0.5f - w * 0.5f);
    polygonShape->Set(points, 7);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = polygonShape;
    fixtureDef.density = 2;
    fixtureDef.friction = BODY_FRICTION;
    fixtureDef.restitution = 0;
    FixtureUserData *bodyFixtureData = new FixtureUserData();
    bodyFixtureData->contactListener = this;
    bodyFixtureData->name = "Body";
    fixtureDef.userData = bodyFixtureData;
    _body_fixture = _body->CreateFixture(&fixtureDef);
//    _body_fixture->SetUserData(&bodyFixtureData);

    addSensor(b2Vec2(-BODY_WIDTH / 2 + 2, BODY_HEIGHT / 2 + 3), b2Vec2(3, 8), SENSOR_ID_FOOT_LEFT);
    addSensor(b2Vec2(+BODY_WIDTH / 2 - 2, BODY_HEIGHT / 2 + 3), b2Vec2(3, 8), SENSOR_ID_FOOT_RIGHT);
}

b2Fixture *Person::addSensor(b2Vec2 pos_px, b2Vec2 size_px, int id) {
    b2PolygonShape *sensorShape = new b2PolygonShape();
    b2Vec2 pos = _world->screenToWorldCoordinates(pos_px.x, pos_px.y);
    size_px *= _world->getCamera().anti_scale_factor;
    sensorShape->SetAsBox(size_px.x, size_px.y, pos, 0);
    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = sensorShape;
    sensorFixtureDef.isSensor = true;
    FixtureUserData *userData = new FixtureUserData();
    userData->id = id;
    userData->name = "Sensor";
    sensorFixtureDef.userData = userData;
    b2Fixture *sensor = _body->CreateFixture(&sensorFixtureDef);
//    sensor->SetUserData(userData);
    (*_sensors)[id] = sensor;
    return sensor;
}

void Person::setPosition(float x, float y) {
    Entity::setPosition(x, y);
    b2Vec2 wp = _world->screenToWorldCoordinates(x, y);
    _body->SetTransform(wp, _body->GetAngle());
}

b2Body *Person::getBody() const {
    return _body;
}

b2Fixture *Person::getSensorById(int id) {
    return _sensors->at(id);
}

FixtureUserData *Person::getSensorDataById(int id) {
    b2Fixture *sensor = _sensors->at(id);
    return (FixtureUserData *) (sensor->GetUserData());
}
