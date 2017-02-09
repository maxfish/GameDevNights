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

    int num_joysticks_connected();

    Joystick *get_joystick_from_id(SDL_JoystickID joystick_id);

    Joystick *getJoystickFromIndex(int joystick_index);

private:
    int _num_joysticks;
    Joystick *_joysticks[MAX_JOYSTICKS];

    void process_event(const SDL_Event &event);
};
