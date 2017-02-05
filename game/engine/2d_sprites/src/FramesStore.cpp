//
// Created by Massimiliano Pesce on 07/12/2016.
//

#include <engine/2d_sprites/include/FramesStore.h>
#include <fstream>
#include <third_parties/json/json.hpp>

FramesStore::FramesStore() {

}

void FramesStore::load(std::string file_path) {
    std::ifstream file_stream(file_path, std::ios::in);

    if (!file_stream) {
        SDL_Log("Error - Couldn't open file '%s'", file_path.c_str());
        return;
    }

    std::string file_content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
    nlohmann::json json = nlohmann::json::parse(file_content.c_str());

}