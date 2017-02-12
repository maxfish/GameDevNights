#pragma once

#include <vector>
#include <engine/core/include/EventsManager.h>
#include <engine/2d_sprites/include/Sprite.h>
#include <engine/2d_map/include/Map.h>
#include "Player.h"

class Graphics;

class Game {
public:
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
