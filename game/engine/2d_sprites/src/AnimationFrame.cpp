//
// Created by Massimiliano Pesce on 20/12/2016.
//

#include <string>
#include <third_parties/json/json.hpp>
#include "engine/2d_sprites/include/AnimationFrame.h"
#include <engine/core/include/Utils.hpp>

AnimationFrame::AnimationFrame(nlohmann::json frame_json) {
    _frame_name = frame_json["frame"];
    _flip_x = Utils::boolFromJsonField(frame_json, "flip_x", false);
    _flip_y = Utils::boolFromJsonField(frame_json, "flip_y", false);
    _delay = Utils::intFromJsonField(frame_json, "delay", 1);
}

AnimationFrame::~AnimationFrame() {

}

int AnimationFrame::getDelay() {
    return _delay;
}

std::string AnimationFrame::getFrameName() {
    return _frame_name;
}

bool AnimationFrame::getFlipX() {
    return _flip_x;
}

bool AnimationFrame::getFlipY() {
    return _flip_y;
}
