//
// Created by Massimiliano Pesce on 07/12/2016.
//

#pragma once

#include <map>
#include <SDL_Image.h>
#include <engine/core/include/Graphics.h>
#include <engine/2d_sprites/include/Frame.h>
#include <engine/2d_sprites/include/Animation.h>

class FramesStore {
public:
    static const int FLAG_FLIP_X = 1;
    static const int FLAG_FLIP_Y = 2;
    static const int FLAG_LOOP_ANIMATION = 16;
//    FLAG_FLIP_X = 1
//    FLAG_FLIP_Y = 2
//    FLAG_CENTER_X = 4
//    FLAG_CENTER_Y = 8
//    FLAG_LOOP_ANIMATION = 16

    FramesStore(Graphics &graphics);

    void load(std::string file_path, std::string file_name);

    SDL_Texture *getImage(std::string file_name);

    Animation *getAnimation(std::string animation_name);

    Frame *getFrame(std::string frame_name);

    void drawFrame(Graphics &graphics, Frame &frame, int dest_x, int dest_y, Uint16 flags);

private:
    Graphics *_graphics;
    std::map<std::string, SDL_Texture *> _images;
    std::map<std::string, Frame *> _frames;
    std::map<std::string, Animation *> _animations;
};
