//
// Created by Massimiliano Pesce on 05/02/17.
//

#pragma once

#include <engine/core/include/Graphics.h>
#include <engine/2d_sprites/include/Sprite.h>

class Entity {
public:
    Entity();

    virtual void update(float gameSpeed);

    virtual void draw(Graphics &graphics);

    virtual void setPosition(int x, int y);

protected:

    SDL_Point _position;
};