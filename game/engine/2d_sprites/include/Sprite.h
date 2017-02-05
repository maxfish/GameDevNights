#pragma once

#include "engine/core/include/Graphics.h"
#include <engine/2d_sprites/include/FramesStore.h>
#include <engine/2d_sprites/include/Animation.h>
#include <engine/2d_sprites/include/Frame.h>
#include <SDL2/SDL.h>

class Sprite {

public:
    static const int FLAG_FLIP_X = 1;
    static const int FLAG_FLIP_Y = 2;
    static const int FLAG_LOOP_ANIMATION = 16;

    Sprite(FramesStore *framesStore);

    virtual ~Sprite();

    virtual void update(float gameSpeed);

    void draw(Graphics &graphics);

    void setPosition(int x, int y);

    void playAnimation(std::string animation_name, Uint16 flags);

    void stopAnimation();

private:
    FramesStore *_framesStore;
    SDL_Point _position;
    Uint16 _flags;

    SDL_Rect _hit_box;
    SDL_Rect _attack_box;

    Frame *_frame;
    Animation *_animation;
    std::string _animation_name;
    Uint8 _animation_frame_index;
    Uint8 _animation_frame_delay;
    bool _animating;

    void setAnimationFrame(Uint8 frame_index);

    void nextAnimationFrame();

    void skipToLastAnimationFrame();

    void updateCollisionBoxes();
};