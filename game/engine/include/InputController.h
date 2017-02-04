//
// Created by max on 02/02/17.
//

#pragma once

#include <SDL_events.h>
#include <vector>
#include <SDL_haptic.h>
#include "Joystick.h"

#define MAX_JOYSTICKS   4

class InputController {
public:
    InputController();

    ~InputController();

    void process_frame_events(const std::vector<SDL_Event> frame_events);
    void process_event(const SDL_Event &event);

    int num_joysticks_connected();

    Joystick *get_joystick_from_id(SDL_JoystickID joystick_id);


private:
    int num_joysticks;
    Joystick joysticks[MAX_JOYSTICKS];
};
