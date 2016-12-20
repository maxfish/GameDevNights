#pragma once

#include "graphics.h"
#include "FramesStore.h"
#include "Frame.h"
#include "Animation.h"
#include <SDL2/SDL.h>

class Sprite {

public:
    Sprite();
    Sprite(FramesStore &framesStore);

    virtual ~Sprite();

    virtual void update(float gameSpeed);

    void draw(Graphics &graphics);

    void setPosition(int x, int y);

private:
    FramesStore _framesStore;
    SDL_Point _position;
    Uint16 _flags;

    Frame _frame;
    Animation _animation;
    std::string _animation_name;
    Uint8 _animation_frame_index;
    Uint8 _animation_frame_delay;
    bool _animating;
};
