//
// Created by Massimiliano Pesce on 07/12/2016.
//

#pragma once

#include <string>
#include <SDL_Image.h>
#include <third_parties/json/json.hpp>


class Frame {
public:
    Frame(std::string frame_name, nlohmann::json frame_json, SDL_Texture* frame_image);

    virtual ~Frame();

    const SDL_Rect getRect();

    const SDL_Rect getHitBox();

    const SDL_Rect getAttackBox();

    const SDL_Point getAnchor();

    SDL_Texture* getImage();

private:
    std::string _frame_name;
    std::string _image_file;
    SDL_Texture *_image;

    SDL_Point _anchor;
    SDL_Rect _rect;
    SDL_Rect _hit_box;
    SDL_Rect _attack_box;
};
