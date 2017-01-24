//
// Created by max on 24/01/17.
//

#pragma once

#include <SDL_events.h>
#include <vector>

class EventsManager {
public:
    EventsManager();
    ~EventsManager();
    void add_frame_event(SDL_Event event);
    void clear_events();

private:
    std::vector<SDL_Event> _frame_events;
};
