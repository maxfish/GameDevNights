#include <engine/2d_sprites/include/Sprite.h>

Sprite::Sprite() {
}

Sprite::Sprite(FramesStore &framesStore) {
    this->_framesStore = framesStore;
}

Sprite::~Sprite() {

}

void Sprite::update(float game_speed) {
    // TODO
}

void Sprite::draw(Graphics &graphics) {
    // TODO
}

void Sprite::setPosition(int x, int y) {
    this->_position.x = x;
    this->_position.y = y;
}
