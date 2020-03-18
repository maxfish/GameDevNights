#pragma once

#include <vector>
#include <engine/core/EventsManager.h>
#include <engine/2d_sprites/bitmap/Sprite.h>
#include <engine/2d_map/Map.h>
#include "player/Player.h"
#include "physics/World.h"

class Graphics;

enum _entityCategory {
    WORLD = 0x0001,
    PLAYER = 0x0002,
    OBJECT = 0x0004
};

class Game {
public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
    static const int FPS = 50;
    static const int FRAME_TIME = 1000 / FPS;

    Game();

    ~Game();

private:
    void gameLoop();

    void draw(Graphics &graphics);

    void update(float game_speed);

    Graphics *_graphics;
    World *_world;
    EventsManager *_eventsManager;
    Player *_player;
    Map *_map;
};
