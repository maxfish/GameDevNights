//
// Created by max on 02/02/17.
//


#include <engine/input/include/InputController.h>
#include <SDL_log.h>

InputController::InputController() {

}

InputController::~InputController() {

}

void InputController::process_frame_events(const std::vector<SDL_Event> frame_events) {
    for (SDL_Event event : frame_events) {
        process_event(event);
    }
}

void InputController::process_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_CONTROLLERDEVICEADDED: {
            // The ID is the index of the joystick being added.
            // This assumes that the joystick is a valid game controller and that init is successful
            int controller_index = event.cdevice.which;
            if (controller_index < MAX_JOYSTICKS) {
                Joystick &joystick = joysticks[controller_index];
                joystick.open(event.cdevice.which);
                SDL_Log("Connected joystick <%u> at index #%d.", joystick.get_joystick_id(), controller_index);
                num_joysticks++;
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
            num_joysticks--;
            break;
        }
//            case SDL_CONTROLLERDEVICEREMAPPED: {
//                // TODO: Remap doesn't work
//                SDL_JoystickID joystick_id = event.cdevice.which;
//                SDL_Log("Remapped joystick <%d>.", joystick_id);
//                break;
//            }

        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP: {
            SDL_JoystickID joystick_id = event.cdevice.which;
            SDL_LogDebug(1, "Event for joystick %d", joystick_id);
            Joystick *joystick = get_joystick_from_id(joystick_id);
            if (joystick != nullptr) {
                if (joystick->is_connected()) {
                    joystick->process_event(event);
                }
            } else {
                SDL_Log("Joystick <%d> not found.", joystick_id);
            }
            break;
        }
        default:
            break;
    }
}

Joystick *InputController::get_joystick_from_id(SDL_JoystickID joystick_id) {
    for (int i = 0; i < MAX_JOYSTICKS; i++) {
        Joystick joystick = joysticks[i];
        if (joystick.is_connected() && joystick.get_joystick_id() == joystick_id) {
            return &joysticks[i];
        }
    }
    return nullptr;
}

int InputController::num_joysticks_connected() {
    return num_joysticks;
}
