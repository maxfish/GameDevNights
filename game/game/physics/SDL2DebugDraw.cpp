//
// Created by max on 03/03/17.
//

#include "SDL2DebugDraw.h"
#include "World.h"


SDL2DebugDraw::SDL2DebugDraw(SDL_Renderer *renderer, World *world) {
    _renderer = renderer;
    _world = world;
}

void SDL2DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    SDL_Point points[vertexCount + 1];
    for (int i = 0; i < vertexCount; i++) {
        b2Vec2 screen_point = _world->worldToScreenCoordinates(vertices[i]);
        points[i] = {(int) screen_point.x, (int) screen_point.y};
    }
    points[vertexCount] = points[0];
    SDL_SetRenderDrawColor(_renderer, (Uint8) (color.r * 256), (Uint8) (color.g * 256), (Uint8) (color.b * 256),
                           (Uint8) (256 * (1 - color.a)));
    SDL_RenderDrawLines(_renderer, points, vertexCount + 1);
}

void SDL2DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    SDL_Point points[vertexCount + 1];
//    SDL_Log("------");
    for (int i = 0; i < vertexCount; i++) {
        b2Vec2 screen_point = _world->worldToScreenCoordinates(vertices[i]);
        points[i] = {(int) screen_point.x, (int) screen_point.y};
//        SDL_Log("point: %d,%d", points[i].x, points[i].y);
    }
    points[vertexCount] = points[0];

    SDL_SetRenderDrawColor(_renderer, (Uint8) (color.r * 256), (Uint8) (color.g * 256), (Uint8) (color.b * 256),
                           (Uint8) (256 * (1 - color.a)));
    SDL_RenderDrawLines(_renderer, points, vertexCount + 1);
}

void SDL2DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {

}

void SDL2DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {

}

void SDL2DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
    SDL_SetRenderDrawColor(_renderer, (Uint8) (color.r * 256), (Uint8) (color.g * 256), (Uint8) (color.b * 256),
                           (Uint8) (256 * (1 - color.a)));
    b2Vec2 s1 = _world->worldToScreenCoordinates(p1);
    b2Vec2 s2 = _world->worldToScreenCoordinates(p2);
    SDL_RenderDrawLine(_renderer, (int) (s1.x), (int) (s1.y), (int) (s2.x),
                       (int) (s2.y));
}

void SDL2DebugDraw::DrawTransform(const b2Transform &xf) {

}

void SDL2DebugDraw::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) {

}
