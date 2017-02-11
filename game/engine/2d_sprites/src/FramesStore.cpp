//
// Created by Massimiliano Pesce on 07/12/2016.
//

#include <engine/2d_sprites/include/FramesStore.h>
#include <engine/2d_sprites/include/Sprite.h>
#include <engine/core/include/Utils.hpp>

FramesStore::FramesStore(Graphics &graphics) {
    _graphics = &graphics;
}

void FramesStore::load(std::string file_path, std::string file_name) {
    nlohmann::json json = Utils::jsonFromFile(file_path + "/" + file_name);
    if (json == nullptr) {
        SDL_Log("Error - Couldn't open file '%s'", file_path.c_str());
        return;
    }

    std::map<std::string, nlohmann::json> meta_data_map = json["meta"];
    _fps = Utils::intFromJsonField(meta_data_map, "fps", DEFAULT_FPS);

    std::map<std::string, nlohmann::json> animations_map = json["animations"];
    for (auto entry : animations_map) {
        std::string animation_name = entry.first;
        nlohmann::json animation_json = entry.second;
        Animation *animation = new Animation(animation_name, animation_json);
        _animations[animation_name] = animation;
    }

    std::map<std::string, nlohmann::json> frames_map = json["frames"];
    for (auto entry : frames_map) {
        std::string frame_name = entry.first;
        nlohmann::json frame_json = entry.second;

        std::string image_file = frame_json["image_file"];
        if (_images[image_file] == nullptr) {
            std::string image_path = file_path + "/" + image_file;
            _images[image_file] = _graphics->loadImage(image_path);
        }

        Frame *frame = new Frame(frame_name, frame_json, _images[image_file]);
        _frames[frame_name] = frame;
    }

    SDL_Log("FramesStore '%s/%s' loaded.", file_path.c_str(), file_name.c_str());
}

SDL_Texture *FramesStore::getImage(std::string file_name) {
    return _images[file_name];
}

Animation *FramesStore::getAnimation(std::string animation_name) {
    return _animations[animation_name];
}

Frame *FramesStore::getFrame(std::string frame_name) {
    return _frames[frame_name];
}
