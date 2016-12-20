//
// Created by Massimiliano Pesce on 07/12/2016.
//

#pragma once

#include <string>
#include <SDL_surface.h>


class Frame {
public:
    Frame();

    virtual ~Frame();

    const SDL_Rect &get_rect() const;

    const SDL_Rect &get_hit_box() const;

    const SDL_Rect &get_attack_box() const;

private:
    std::string _frame_name;
    std::string _image_file;
    SDL_Surface *_image;

    SDL_Point _anchor;
    SDL_Rect _rect;
    SDL_Rect _hit_box;
    SDL_Rect _attack_box;
};
