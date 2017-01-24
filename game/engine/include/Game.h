#pragma once

#include <vector>
#include "sprite.h"
#include "EventsManager.h"

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
    Sprite _player;
};
