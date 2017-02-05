//
// Created by Massimiliano Pesce on 05/02/17.
//

#include <engine/entities/include/Entity.h>

Entity::Entity() {
}

void Entity::setPosition(int x, int y) {
    _position.x = x;
    _position.y = y;
}

void Entity::update(float game_speed) {
}

void Entity::draw(Graphics &graphics) {
    // TODO
}
