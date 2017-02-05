#include <globals.h>
#include <engine/2d_sprites/include/Sprite.h>

Sprite::Sprite() {
}

Sprite::Sprite(FramesStore &framesStore) {
    this->_framesStore = framesStore;

}

Sprite::~Sprite() {

}

void Sprite::update(float game_speed) {
    move(4, 0);
}

void Sprite::draw(Graphics &graphics) {
    auto image = graphics.loadImage("resources/images/sprites/boy.png");
    int width, height;
    SDL_QueryTexture(image, NULL, NULL, &width, &height);

    SDL_Rect sourceRect = {0, 0, width, height};
    SDL_Rect destinationRectangle = {this->_position.x, this->_position.y, width, height};
    graphics.blitTexture(image, &sourceRect, &destinationRectangle);
}

void Sprite::move(int x, int y) {
    int new_x = this->_position.x + x;
    if (new_x >= globals::SCREEN_WIDTH)
        new_x -= globals::SCREEN_WIDTH;
    int new_y = this->_position.y + y;
    if (new_y >= globals::SCREEN_HEIGHT)
        new_y -= globals::SCREEN_HEIGHT;

    this->_position.x = new_x;
    this->_position.y = new_y;
}

void Sprite::setPosition(int x, int y) {
    this->_position.x = x;
    this->_position.y = y;
}
