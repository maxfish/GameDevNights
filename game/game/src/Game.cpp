#include <SDL2/SDL.h>
#include <engine/input/include/InputController.h>
#include "game/include/Game.h"
#include "engine/input/include/Keyboard.h"
#include "globals.h"

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->_eventsManager = new EventsManager();
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics = Graphics("Game", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
    Keyboard input;
    SDL_Event event;

    InputController *inputController = new InputController();

    _player = new Player(graphics, inputController, 0);
    _player->setPosition(120, 200);

    long time_accumulator = 0;
    float game_speed = 1.0f;

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
            } else {
                _eventsManager->add_frame_event(event);
            }
        }

        inputController->process_frame_events(_eventsManager->get_frame_events());

        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            return;
        }

        this->update(game_speed);

        long elapsed_time = SDL_GetTicks() - start_time;
        time_accumulator += elapsed_time;
        game_speed = elapsed_time / float(globals::FRAME_TIME);

        if (time_accumulator >= globals::FRAME_TIME) {
            time_accumulator = 0;
            this->draw(graphics);
        }

        this->_eventsManager->clear_events();
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear(40, 150, 70, 255);
    SDL_SetRenderDrawColor(graphics.getRenderer(), 0,0,0,255);
    SDL_RenderDrawLine(graphics.getRenderer(), 0, 200, 500, 200);
    SDL_RenderDrawLine(graphics.getRenderer(), 120, 0, 120, 200);

    _player->draw(graphics);

    graphics.flip();
}

void Game::update(float game_speed) {
    _player->handleInput(game_speed);
    _player->update(game_speed);
}

