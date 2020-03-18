//
// Created by max on 03/03/17.
//

#ifndef GAME_SDL2DEBUGDRAW_H
#define GAME_SDL2DEBUGDRAW_H


#include <Box2D/Common/b2Draw.h>
#include <SDL2/SDL_render.h>
#include "World.h"

class SDL2DebugDraw : public b2Draw {
public:
    SDL2DebugDraw(SDL_Renderer *renderer, World *world);

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) override;

    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) override;

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

    void DrawTransform(const b2Transform &xf) override;

    void DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) override;

private:
    SDL_Renderer *_renderer;
    World *_world;
};


#endif //GAME_SDL2DEBUGDRAW_H
