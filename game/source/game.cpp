#include <SDL2/SDL.h>
#include "game.h"
#include "input.h"
#include "FramesStore.h"

namespace {
    const int FPS = 50;
    //Max amount of time that a frame can last
    const int FRAME_TIME = 1000 / FPS;
}


Game::Game() {
    //Load all the things
    SDL_Init(SDL_INIT_EVERYTHING);

    //Calls main loop
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {

    Graphics graphics;
    Input input;

    //Event that has happened for this particular frame
    SDL_Event event;

    FramesStore framesStore = FramesStore();
//    this->_player2 = Sprite(framesStore);

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
        if (elapsed_time < FRAME_TIME) {
            SDL_Delay(FRAME_TIME - elapsed_time);
            game_speed = 1;
        } else {
            game_speed = elapsed_time / FRAME_TIME;
        }
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();

//    this->_player.draw(graphics, 100, 100);

    graphics.flip();
}

void Game::update(float game_speed) {

}

