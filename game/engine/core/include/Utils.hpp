//
// Created by Massimiliano Pesce on 05/02/17.
//

#pragma once

#include <fstream>
#include <SDL_Rect.h>
#include <third_parties/json/json.hpp>

namespace Utils {

    inline nlohmann::json jsonFromFile(std::string file_path) {
        std::ifstream file_stream(file_path, std::ios::in);

        if (!file_stream) {
            return nullptr;
        }

        std::string file_content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
        return nlohmann::json::parse(file_content.c_str());
    }

    inline SDL_Rect rectFromJson(nlohmann::json json_rect) {
        SDL_Rect r;
        r.x = json_rect["x"];
        r.y = json_rect["y"];
        r.w = json_rect["width"];
        r.h = json_rect["height"];
        return r;
    }

    inline bool boolFromJsonField(nlohmann::json json_object, std::string field_key, bool default_value) {
        if (json_object.find(field_key) != json_object.end()) {
            return bool(json_object[field_key]);
        } else {
            return default_value;
        }
    }

    inline int intFromJsonField(nlohmann::json json_object, std::string field_key, int default_value) {
        if (json_object.find(field_key) != json_object.end()) {
            return json_object[field_key];
        } else {
            return default_value;
        }
    }
}