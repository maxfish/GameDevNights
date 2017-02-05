//
// Created by Massimiliano Pesce on 07/12/2016.
//

#include <engine/2d_sprites/include/Frame.h>
#include <engine/core/include/Utils.hpp>

Frame::Frame(std::string frame_name, nlohmann::json frame_json, SDL_Texture *frame_image) {
    _frame_name = frame_name;
    _image_file = frame_json["image_file"];
    _image = frame_image;

    if (frame_json.find("anchor") != frame_json.end()) {
        nlohmann::json anchor_json = frame_json["anchor"];
        _anchor.x = anchor_json["x"];
        _anchor.y = anchor_json["y"];
    } else {
        _anchor.x = _anchor.y = 0;
    }

    // Frame rect within the image
    if (frame_json.find("rect") != frame_json.end()) {
        _rect = Utils::rectFromJson(frame_json["rect"]);
    } else {
        // The whole image is used for the frame
        _rect.x = _rect.y = 0;
        SDL_QueryTexture(_image, NULL, NULL, &_rect.w, &_rect.h);
    }

    if (frame_json.find("attack_box") != frame_json.end()) {
        _attack_box = Utils::rectFromJson(frame_json["attack_box"]);
    }
    if (frame_json.find("hit_box") != frame_json.end()) {
        _hit_box = Utils::rectFromJson(frame_json["hit_box"]);
    }
}

Frame::~Frame() {

}

const SDL_Rect Frame::getRect() {
    return _rect;
}

const SDL_Rect Frame::getHitBox() {
    return _hit_box;
}

const SDL_Rect Frame::getAttackBox() {
    return _attack_box;
}

const SDL_Point Frame::getAnchor() {
    return _anchor;
}

SDL_Texture* Frame::getImage() {
    return _image;
}
