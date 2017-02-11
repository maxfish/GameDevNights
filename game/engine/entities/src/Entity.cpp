//
// Created by Massimiliano Pesce on 05/02/17.
//

#include <engine/entities/include/Entity.h>

Entity::Entity() {
}

void Entity::setPosition(float x, float y) {
    _position_x = x;
    _position_y = y;
}

void Entity::update(float game_speed) {
}

void Entity::draw(Graphics &graphics) {
    // TODO
}
