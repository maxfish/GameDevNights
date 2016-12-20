#pragma once

#include "sprite.h"

class Graphics;

class Game {
public:
    Game();
    ~Game();

private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float game_speed);

    Sprite _player;
};
