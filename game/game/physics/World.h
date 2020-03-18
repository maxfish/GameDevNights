//
// Created by max on 22/02/17.
//

#pragma once

#include <vector>
#import "engine/core/Graphics.h"
#import <Box2D/Box2D.h>

struct WorldCamera {
    float translation_x = 0.0f;
    float translation_y = 0.0f;
    bool vertical_flip = true;
    float scale_factor = 30.0f;
    float anti_scale_factor = 1 / scale_factor;
    float offset_x = 0;
    float offset_y = 0;
    float width = 0;
    float height = 0;
};

class World {
public:
    World(Graphics *graphics, float32 width_px, float32 height_px, b2Vec2 gravity);

    ~World();

    b2World *getB2World();

    WorldCamera getCamera();

    void step(float32 timeElapsed);

    b2Body *createBox(float32 pos_x, float32 pos_y, float32 half_width, float32 half_height, float32 angle, float32 density, bool dynamic);

    b2Body *createEdge(b2Vec2 from, b2Vec2 to);

    b2Vec2 worldToScreenCoordinates(b2Vec2 world);

    b2Vec2 worldToScreenCoordinates(float x, float y);

    b2Vec2 screenToWorldCoordinates(b2Vec2 screen);

    b2Vec2 screenToWorldCoordinates(float screenX, float screenY);

    void debugDraw();

private:
    b2World *_world;
    b2Vec2 _gravity;

    WorldCamera _camera;

    float map_coords(float value, float istart, float istop, float ostart, float ostop);
};
