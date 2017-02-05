//
// Created by max on 24/01/17.
//

#include <SDL2/SDL.h>
#include <engine/core/include/EventsManager.h>

EventsManager::EventsManager() {
    this->_frame_events = {};
}

EventsManager::~EventsManager() {
}

void EventsManager::add_frame_event(SDL_Event event) {
    this->_frame_events.push_back(event);
//    SDL_Log("Event added! (%d)", this->_frame_events.size());
}

void EventsManager::clear_events() {
    this->_frame_events.clear();
}

const std::vector<SDL_Event> &EventsManager::get_frame_events() const {
    return _frame_events;
}


