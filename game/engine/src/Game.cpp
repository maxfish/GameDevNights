#include <SDL2/SDL.h>
#include "game.h"
#include "input.h"
#include "globals.h"

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics = Graphics(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
    Input input;

    SDL_Event event;
    FramesStore framesStore = FramesStore();
    this->_player = Sprite(framesStore);

    auto game_speed = 1;

    while (true) {
        auto start_time = SDL_GetTicks();

        input.beginNewFrame();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.repeat == 0) {
                    input.keyDownEvent(event);
                }
            }// if a key was released
            else if (event.type == SDL_KEYUP) {
                input.keyUpEvent(event);
            }//if the user hits the exit button
            else if (event.type == SDL_QUIT) {
                return;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            return;
        }

        this->update(game_speed);
        this->draw(graphics);

        auto elapsed_time = SDL_GetTicks() - start_time;
        if (elapsed_time < globals::FRAME_TIME) {
            SDL_Delay(globals::FRAME_TIME - elapsed_time);
            game_speed = 1;
        } else {
            game_speed = elapsed_time / globals::FRAME_TIME;
        }
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();

    this->_player.draw(graphics);

    graphics.flip();
}

void Game::update(float game_speed) {
    this->_player.setPosition(100, 100);
    this->_player.update(game_speed);
}

