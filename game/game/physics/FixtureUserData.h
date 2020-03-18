//
// Created by max on 05/03/17.
//

#pragma once

#include <string>

struct FixtureUserData {
    int num_contacts = 0;
    int id = 0;
    b2ContactListener *contactListener = nullptr;
    std::string name;
};