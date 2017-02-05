//
// Created by Massimiliano Pesce on 07/12/2016.
//

#include <engine/core/include/Frame.h>

Frame::Frame() {}

Frame::~Frame() {

}

const SDL_Rect &Frame::get_rect() const {
    return _rect;
}

const SDL_Rect &Frame::get_hit_box() const {
    return _hit_box;
}

const SDL_Rect &Frame::get_attack_box() const {
    return _attack_box;
}
