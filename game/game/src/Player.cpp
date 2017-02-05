//
// Created by max on 05/02/17.
//

#include <globals.h>
#include "Player.h"

Player::Player() {
    Entity();
    _sprite = new Sprite();
}

void Player::update(float gameSpeed) {
    int x =4;
    int y =0;
    int new_x = this->_position.x + x;
    if (new_x >= globals::SCREEN_WIDTH)
        new_x -= globals::SCREEN_WIDTH;
    int new_y = this->_position.y + y;
    if (new_y >= globals::SCREEN_HEIGHT)
        new_y -= globals::SCREEN_HEIGHT;

    this->_position.x = new_x;
    this->_position.y = new_y;
}

void Player::draw(Graphics &graphics) {
    auto image = graphics.loadImage("resources/images/sprites/boy.png");
    int width, height;
    SDL_QueryTexture(image, NULL, NULL, &width, &height);

    SDL_Rect sourceRect = {0, 0, width, height};
    SDL_Rect destinationRectangle = {_position.x, _position.y, width, height};
    graphics.blitTexture(image, &sourceRect, &destinationRectangle);
}

