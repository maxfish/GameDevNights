//
// Created by max on 24/01/17.
//

#pragma once

#include <SDL_events.h>
#include <vector>
#include <SDL_haptic.h>

const int MAX_BUTTONS = 24;

class Joystick {
public:
    Joystick();

    ~Joystick();

    void open(int device_index);

    void close();

    bool is_connected();

    bool isButtonPressed(SDL_GameControllerButton button_id);
    bool isButtonDown(SDL_GameControllerButton button_id);
    bool isButtonReleased(SDL_GameControllerButton button_id);

    SDL_JoystickID get_joystick_id();

    void process_frame_events(const std::vector<SDL_Event> frame_events);

private:
    bool _connected;
    SDL_GameController *_sdl_controller;
    SDL_Joystick *_sdl_joystick;
    SDL_JoystickID _sdl_joystick_id;
    SDL_Haptic *_sdl_haptic;

    bool _buttonPressed[MAX_BUTTONS];
    bool _buttonReleased[MAX_BUTTONS];
    bool _buttonDown[MAX_BUTTONS];

    void _process_event(const SDL_Event &event);
};
