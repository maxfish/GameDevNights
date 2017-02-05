//
// Created by max on 05/02/17.
//

#pragma once

#include <engine/2d_sprites/include/Sprite.h>
#include <engine/entities/include/Entity.h>

class Player : public Entity {
public:
    Player();

    void update(float gameSpeed) override;

    void draw(Graphics &graphics) override;

private:
    FramesStore *_framesStore;
    Sprite *_sprite;
};
