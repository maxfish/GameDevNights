//
// Created by Massimiliano Pesce on 09/12/2016.
//

#include <engine/2d_sprites/include/Animation.h>

Animation::Animation(std::string animation_name, nlohmann::json animation_json) {
    _animation_name = animation_name;

    std::vector<nlohmann::json> frames_list = animation_json["frames"];

    for (auto frame_json : frames_list) {
        AnimationFrame *frame = new AnimationFrame(frame_json);
        _frames.push_back(frame);
    }
}

Animation::~Animation() {

}

AnimationFrame* Animation::getFrame(unsigned int frame_index) {
    return _frames[frame_index];
}

int Animation::getFramesCount() {
    return (int) _frames.size();
}