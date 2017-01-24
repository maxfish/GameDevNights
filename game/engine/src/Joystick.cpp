//
// Created by max on 24/01/17.
//

#include <SDL_events.h>
#include <Joystick.h>
#include <SDL_log.h>

Joystick::~Joystick() {

}

void Joystick::open(int device_id) {
    _sdl_controller = SDL_GameControllerOpen(device_id);
    _sdl_joystick = SDL_GameControllerGetJoystick(_sdl_controller);
    _sdl_joystick_id = SDL_JoystickInstanceID(_sdl_joystick);
//  TODO: this should be set when the device is plugged in
    _connected = true;

    if (SDL_JoystickIsHaptic(_sdl_joystick)) {
        _sdl_haptic = SDL_HapticOpenFromJoystick(_sdl_joystick);
        SDL_Log("Joystick> Haptic Effects: %d\n", SDL_HapticNumEffects(_sdl_haptic));
        SDL_Log("Joystick> Haptic Query: %x\n", SDL_HapticQuery(_sdl_haptic));
        if (SDL_HapticRumbleSupported(_sdl_haptic)) {
            if (SDL_HapticRumbleInit(_sdl_haptic) != 0) {
                SDL_Log("Joystick> Haptic Rumble Init: %s\n", SDL_GetError());
                SDL_HapticClose(_sdl_haptic);
                _sdl_haptic = nullptr;
            }
        } else {
            SDL_HapticClose(_sdl_haptic);
            _sdl_haptic = nullptr;
        }
    }

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
    }
}

void Joystick::process_frame_events(const std::vector<SDL_Event> frame_events) {
    for(SDL_Event event : frame_events) {
        process_event(event);
    }
}

int Joystick::process_event(SDL_Event &event) {
    switch (event.type) {
        case SDL_CONTROLLERAXISMOTION: {
            // handle axis motion
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP: {
            SDL_Log("------");
            break;
        }
//        case SDL_CONTROLLERDEVICEADDED: {
//            if (event.cdevice.which < MAX_CONTROLLERS) {
//                JoypadController &jc = s_controllers[event.cdevice.which];
//                jc.Open(event.cdevice.which);
//            }
//            break;
//        }
//        case SDL_CONTROLLERDEVICEREMOVED: {
//            int cIndex = GetControllerIndex(event.cdevice.which);
//            if (cIndex < 0) return 0; // unknown controller?
//            JoypadController &jc = ms_controllers[cIndex];
//            jc.Close();
//            break;
//        }
    }
    return 0;
}

