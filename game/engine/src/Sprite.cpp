#include "sprite.h"

Sprite::Sprite() {
}

Sprite::Sprite(FramesStore &framesStore) {
    this->_framesStore = framesStore;

}

Sprite::~Sprite() {

}

void Sprite::update(float game_speed) {

}

void Sprite::draw(Graphics &graphics) {
//    SDL_Rect destinationRectangle = {x, y, (this->_sourceRect.w * globals::SPRITE_SCALE),
//                                     (this->_sourceRect.h * globals::SPRITE_SCALE)};
//    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::setPosition(int x, int y) {
    this->_position.x = x;
    this->_position.y = y;
}
