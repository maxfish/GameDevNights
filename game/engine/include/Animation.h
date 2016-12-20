//
// Created by Massimiliano Pesce on 09/12/2016.
//

#pragma once


#include <string>
#include <list>
#include "Frame.h"

class Animation {
public:
    Animation(const std::string &_animation_name);

    virtual ~Animation();

private:
    std::string _animation_name;
    std::list<Frame> _frames;
};
