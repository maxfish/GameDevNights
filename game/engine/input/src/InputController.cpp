//
// Created by max on 02/02/17.
//


#include <engine/input/include/InputController.h>
#include <SDL_log.h>

InputController::InputController() {
    for (int i=0; i<MAX_JOYSTICKS; i++) {
        _joysticks[i] = new Joystick();
    }
}

InputController::~InputController() {

}

void InputController::process_frame_events(const std::vector<SDL_Event> frame_events) {
    // TODO: We need to use an event filter to optimize this
    for (SDL_Event event : frame_events) {
        process_event(event);
    }

    for (Joystick *joystick : _joysticks) {
        if (joystick->is_connected()) {
            joystick->process_frame_events(frame_events);
        }
    }
}

void InputController::process_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_CONTROLLERDEVICEADDED: {
            // The ID is the index of the joystick being added.
            // This assumes that the joystick is a valid game controller and that init is successful
            int controller_index = event.cdevice.which;
            if (controller_index < MAX_JOYSTICKS) {
                Joystick *joystick = _joysticks[controller_index];
                joystick->open(event.cdevice.which);
                SDL_Log("Connected joystick <%u> at index #%d.", joystick->get_joystick_id(), controller_index);
                _num_joysticks++;
            } else {
                SDL_Log("Too many joysticks connected. Max num allowed is %u", MAX_JOYSTICKS);
            }
            break;
        }
        case SDL_CONTROLLERDEVICEREMOVED: {
            // The ID is the Joystick ID of an already connected device
            SDL_JoystickID joystick_id = event.cdevice.which;
            Joystick *joystick = get_joystick_from_id(joystick_id);
            if (joystick != nullptr) {
                joystick->close();
                SDL_Log("Disconnected joystick <%d>.", joystick_id);
            } else {
                // TEMP: This happens with the XBox360 Driver for OSX. Joysticks' indices are shuffled during hot-plugging
                SDL_Log("Couldn't find an index for joystick <%d>.", joystick_id);
            }
            _num_joysticks--;
            break;
        }
        default:
            break;
    }
}

Joystick *InputController::get_joystick_from_id(SDL_JoystickID joystick_id) {
    for (int i = 0; i < MAX_JOYSTICKS; i++) {
        Joystick *joystick = _joysticks[i];
        if (joystick->is_connected() && joystick->get_joystick_id() == joystick_id) {
            return joystick;
        }
    }
    return nullptr;
}

Joystick *InputController::getJoystickFromIndex(int joystick_index) {
    Joystick *joystick = _joysticks[joystick_index];
    if (joystick->is_connected()) {
        return _joysticks[joystick_index];
    } else {
        SDL_Log("Joystick #%d <%p> not initialized.", joystick_index, &joystick);
        return nullptr;
    }
}

int InputController::num_joysticks_connected() {
    return _num_joysticks;
}
