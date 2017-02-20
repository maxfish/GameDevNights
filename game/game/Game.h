#pragma once

#include <vector>
#include <engine/core/EventsManager.h>
#include <engine/2d_sprites/Sprite.h>
#include <engine/2d_map/Map.h>
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
