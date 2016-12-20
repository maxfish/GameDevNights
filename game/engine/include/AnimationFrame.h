//
// Created by Massimiliano Pesce on 20/12/2016.
//

#pragma once

#include <string>

class AnimationFrame {
public:
    AnimationFrame(const std::string &_frame_name);

    virtual ~AnimationFrame();

private:
    std::string _frame_name;
    bool _flip_x;
    bool _flip_y;
    int _delay;
};
