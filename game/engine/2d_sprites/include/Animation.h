//
// Created by Massimiliano Pesce on 09/12/2016.
//

#pragma once

#include <string>
#include <third_parties/json/json.hpp>
#include <engine/2d_sprites/include/AnimationFrame.h>


class Animation {
public:
    Animation(std::string animation_name, nlohmann::json animation_json);

    ~Animation();

    AnimationFrame *getFrame(unsigned int frame_index);

    int getFramesCount();

private:
    std::string _animation_name;
    std::vector<AnimationFrame *> _frames;
};
