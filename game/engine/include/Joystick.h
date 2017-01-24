//
// Created by max on 24/01/17.
//

#pragma once

#include <SDL_events.h>
#include <vector>
#include <SDL_haptic.h>

class Joystick {
public:
    Joystick() : _connected(false), _sdl_controller(nullptr), _sdl_joystick_id(-1), _sdl_haptic(nullptr) {}
    ~Joystick();
    void open(int device_id);
    void close();
    void process_frame_events(const std::vector<SDL_Event> frame_events);

private:
    int process_event(SDL_Event &event);

    bool _connected;
    SDL_GameController *_sdl_controller;
    SDL_Joystick *_sdl_joystick;
    SDL_JoystickID _sdl_joystick_id;
    SDL_Haptic *_sdl_haptic;
};
