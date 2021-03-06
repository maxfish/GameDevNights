#include <SDL2/SDL.h>
#include <engine/input/InputController.h>
#include <engine/core/Utils.hpp>
#include <externals/box2d/Box2D/Box2D/Dynamics/b2World.h>
#include "Game.h"
#include "engine/input/Keyboard.h"

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->_eventsManager = new EventsManager();

    b2World *world = new b2World(b2Vec2(float32(0), float32(10)));
    this->gameLoop();
}

Game::~Game() {
    delete(this->_eventsManager);
}

void Game::gameLoop() {
    Graphics graphics = Graphics("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    Keyboard input;
    SDL_Event event;

    InputController *inputController = new InputController();

    _map = new Map(graphics);
    _map->loadFromJSON("resources/maps", "test.json");
    _map->setOffset({0,0});

    _player = new Player(graphics, inputController, 0);
    _player->setPosition(120, 200);

    long time_accumulator = 0;
    float game_speed = 1.0f;

    long prev_time = SDL_GetTicks();
    while (true) {
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
                break;
            } else {
                _eventsManager->add_frame_event(event);
            }
        }

        inputController->process_frame_events(_eventsManager->get_frame_events());

        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
            break;
        }

        long elapsed_time = SDL_GetTicks() - prev_time;
//        time_accumulator += elapsed_time;
        if (elapsed_time >= Game::FRAME_TIME) {
            game_speed = elapsed_time / float(Game::FRAME_TIME);
//            SDL_Log("elapsed:%d speed:%f", elapsed_time, game_speed);
//            time_accumulator -= globals::FRAME_TIME;
            this->update(game_speed);
            this->draw(graphics);
            prev_time = SDL_GetTicks();
        }
        this->_eventsManager->clear_events();
    }

    SDL_Quit();
}

void Game::draw(Graphics &graphics) {
    graphics.clear(40, 150, 70, 255);
    _map->draw();

    SDL_SetRenderDrawColor(graphics.getRenderer(), 0,0,0,255);
//    SDL_RenderDrawLine(graphics.getRenderer(), 0, 200, 500, 200);
//    SDL_RenderDrawLine(graphics.getRenderer(), 120, 0, 120, 200);

    _player->draw(graphics);

    graphics.flip();
}

static int pos = 0;

void Game::update(float game_speed) {
//    pos += 1 * game_speed;
//    _map->setOffset({0,0});

    _player->handleInput(game_speed);
    _player->update(game_speed);
}

