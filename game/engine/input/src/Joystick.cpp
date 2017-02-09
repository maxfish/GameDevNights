//
// Created by max on 24/01/17.
//

#include <SDL_events.h>
#include <engine/input/include/Joystick.h>
#include <SDL_log.h>

Joystick::Joystick() {
    _connected = false;
    _sdl_controller = nullptr;
    _sdl_joystick_id = -1;
    _sdl_haptic = nullptr;
}

Joystick::~Joystick() {

}

void Joystick::open(int device_index) {
    _sdl_controller = SDL_GameControllerOpen(device_index);
    _sdl_joystick = SDL_GameControllerGetJoystick(_sdl_controller);
    _sdl_joystick_id = SDL_JoystickInstanceID(_sdl_joystick);

    //TODO: handle errors here

    SDL_Log("Opened Joystick %i name:'%s' axes:%d btns:%d balls:%d mapping:%s",
            device_index, SDL_JoystickName(_sdl_joystick), SDL_JoystickNumAxes(_sdl_joystick),
            SDL_JoystickNumButtons(_sdl_joystick), SDL_JoystickNumBalls(_sdl_joystick),
            SDL_GameControllerMapping(_sdl_controller) ? "available" : "missing"
    );

    if (SDL_JoystickIsHaptic(_sdl_joystick)) {
        _sdl_haptic = SDL_HapticOpenFromJoystick(_sdl_joystick);
//        SDL_Log("Joystick> Haptic Effects: %d\n", SDL_HapticNumEffects(_sdl_haptic));
//        SDL_Log("Joystick> Haptic Query: %x\n", SDL_HapticQuery(_sdl_haptic));
        if (SDL_HapticRumbleSupported(_sdl_haptic)) {
            if (SDL_HapticRumbleInit(_sdl_haptic) != 0) {
//                SDL_Log("Joystick> Haptic Rumble Init: %s\n", SDL_GetError());
                SDL_HapticClose(_sdl_haptic);
                _sdl_haptic = nullptr;
            }
        } else {
            SDL_HapticClose(_sdl_haptic);
            _sdl_haptic = nullptr;
        }
    }

    memset(_buttonPressed, 0, sizeof _buttonPressed);
    memset(_buttonDown, 0, sizeof _buttonDown);
    memset(_buttonReleased, 0, sizeof _buttonReleased);
    _connected = true;
}

void Joystick::close() {
    if (_connected) {
        _connected = false;
        if (_sdl_haptic) {
            SDL_HapticClose(_sdl_haptic);
            _sdl_haptic = nullptr;
        }
        SDL_GameControllerClose(_sdl_controller);
        _sdl_controller = nullptr;
        _sdl_joystick = nullptr;
        _sdl_joystick_id = -1;
    }
}

bool Joystick::is_connected() {
    return _connected;
}

bool Joystick::isButtonPressed(SDL_GameControllerButton button_id) {
    if (button_id < 0) {
        return false;
    }
    return _buttonPressed[button_id];
}

bool Joystick::isButtonDown(SDL_GameControllerButton button_id) {
    if (button_id < 0) {
        return false;
    }
    return _buttonDown[button_id];
}

bool Joystick::isButtonReleased(SDL_GameControllerButton button_id) {
    if (button_id < 0) {
        return false;
    }
    return _buttonReleased[button_id];
}

SDL_JoystickID Joystick::get_joystick_id() {
    return _sdl_joystick_id;
}

void Joystick::process_frame_events(const std::vector<SDL_Event> frame_events) {
    memset(_buttonPressed, 0, sizeof _buttonPressed);
    memset(_buttonReleased, 0, sizeof _buttonReleased);

    for (SDL_Event event : frame_events) {
        _process_event(event);
    }
}

void Joystick::_process_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_CONTROLLERAXISMOTION: {
            // handle axis motion
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP: {
            if (event.cbutton.which == _sdl_joystick_id) {
                SDL_GameControllerButton button_id = (SDL_GameControllerButton) event.cbutton.button;
                if (button_id < 0) {
                    SDL_Log("Button not recognized/mapped");
                    break;
                }

                if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                    SDL_Log("Button <%d> pressed", button_id);
                    _buttonPressed[button_id] = true;
                    _buttonDown[button_id] = true;
                } else if (event.type == SDL_CONTROLLERBUTTONUP) {
                    SDL_Log("Button <%d> released", button_id);
                    _buttonReleased[button_id] = true;
                    _buttonDown[button_id] = false;
                }
            }
            break;
        }
        default:
            break;
    }
}

