//
// Created by Massimiliano Pesce on 07/12/2016.
//

#pragma once

#include <map>
#include <SDL_surface.h>
#include "Frame.h"
#include "Animation.h"

class FramesStore {
public:
//    FLAG_FLIP_X = 1
//    FLAG_FLIP_Y = 2
//    FLAG_CENTER_X = 4
//    FLAG_CENTER_Y = 8
//    FLAG_LOOP_ANIMATION = 16

    FramesStore();

private:
    std::map<std::string, SDL_Surface*> _images;
    std::map<std::string, Frame> _frames;
    std::map<std::string, Animation> _animations;
};
