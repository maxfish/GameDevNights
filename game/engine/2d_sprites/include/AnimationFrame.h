//
// Created by Massimiliano Pesce on 20/12/2016.
//

#pragma once

#include <string>

class AnimationFrame {
public:
    AnimationFrame(nlohmann::json frame_json);

    virtual ~AnimationFrame();

    int getDelay();

    std::string getFrameName();

    bool getFlipX();

    bool getFlipY();

private:
    std::string _frame_name;
    bool _flip_x;
    bool _flip_y;
    int _delay;
};
