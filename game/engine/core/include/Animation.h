//
// Created by Massimiliano Pesce on 09/12/2016.
//

#pragma once

#include <string>
#include <list>
#include "Frame.h"

class Animation {
public:
    Animation();

    virtual ~Animation();

private:
    std::string _animation_name;
    std::list<Frame> _frames;
};
