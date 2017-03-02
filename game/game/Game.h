#pragma once

#include <vector>
#include <engine/core/EventsManager.h>
#include <engine/2d_sprites/bitmap/Sprite.h>
#include <engine/2d_map/Map.h>
#include "Player.h"

class Graphics;

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

    EventsManager *_eventsManager;
    Player *_player;
    Map *_map;
};
