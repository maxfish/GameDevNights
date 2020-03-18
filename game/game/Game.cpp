#include <SDL2/SDL.h>
#include <engine/input/InputController.h>
#include <engine/core/Utils.hpp>
#include <externals/box2d/Box2D/Box2D/Dynamics/b2World.h>
#include "Game.h"
#include "engine/input/Keyboard.h"
#include "physics/ContactListener.h"

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->_eventsManager = new EventsManager();
    _graphics = new Graphics("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    _world = new World(_graphics, SCREEN_WIDTH, SCREEN_HEIGHT, b2Vec2(float32(0), -float32(10)));

    _world->createEdge(b2Vec2(-400,SCREEN_HEIGHT-2), b2Vec2(SCREEN_WIDTH +400, SCREEN_HEIGHT-2));
//    _world->createBox(SCREEN_WIDTH/2, 300, SCREEN_WIDTH, 30, -0.6, false);
    _world->createBox(0, 200, 200, 20, -0.5, 1, false);
    _world->createBox(0, 400, 300, 20, -0.1, 1, false);
    _world->createBox(100, 10, 40, 40, 0, 3, true);
    _world->createBox(450, 10, 30, 30, 0, 12, true);

    _world->createBox(605, 330, 40, 40, 0, 6, true);
    _world->createBox(600, 390, 20, 20, 0, 6, true);

    b2ContactListener *contactListener = new ContactListener();
    _world->getB2World()->SetContactListener(contactListener);

    this->gameLoop();
}

Game::~Game() {
    delete(_eventsManager);
    delete(_world);
    delete(_graphics);
}

void Game::gameLoop() {
    Keyboard input;
    SDL_Event event;

    InputController *inputController = new InputController();

    Graphics graphics = *_graphics;
    _map = new Map(graphics);
    _map->loadFromJSON("resources/maps", "test.json");
    _map->setOffset({0,0});

    _player = new Player(graphics, _world, inputController, 0);
    _player->setPosition(100, 200);

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
//    _map->draw();

//    SDL_SetRenderDrawColor(graphics.getRenderer(), 0,0,0,255);
//    SDL_RenderDrawLine(graphics.getRenderer(), 0, 200, 500, 200);
//    SDL_RenderDrawLine(graphics.getRenderer(), 120, 0, 120, 200);

    _player->draw(graphics);
    _world->debugDraw();

    graphics.flip();
}

static int pos = 0;

void Game::update(float game_speed) {
//    pos += 1 * game_speed;
//    _map->setOffset({0,0});

//    _world->Step(1,6,2);
//    _world->Step(0.4, 8, 3);
    float32 timeStep = game_speed*FRAME_TIME;
    _world->step(0.05);

    _player->handleInput(0.001);
    _player->update(game_speed);
}

