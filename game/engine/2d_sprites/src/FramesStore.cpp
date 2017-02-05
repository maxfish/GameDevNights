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

void FramesStore::drawFrame(Graphics &graphics, Frame &frame, int dest_x, int dest_y, Uint16 flags) {
    SDL_Rect rect = frame.getRect();
    int w = rect.w;
    int h = rect.h;

    int x1 = rect.x;
    int y1 = rect.y;

    int anchor_x = frame.getAnchor().x;
    int anchor_y = frame.getAnchor().y;

    bool flip_x = false;
    bool flip_y = false;

    if ((flags & Sprite::FLAG_FLIP_X) > 0) {
        anchor_x = w - anchor_x;
        flip_x = true;
    }
    if ((flags & Sprite::FLAG_FLIP_Y) > 0) {
        anchor_y = h - anchor_y;
        flip_y = true;
    }

    int x_pos = dest_x - anchor_x;
    int y_pos = dest_y - anchor_y;

//        image_to_draw = pygame.transform.flip(frame.image, flip_x, flip_y)
//        # g.drawImage(img, xPos, yPos, xPos + w, yPos + h, x1, y1, x2, y2, null);
    SDL_Rect dest_rect;
    dest_rect.x = x_pos;
    dest_rect.y = y_pos;
    dest_rect.w = w;
    dest_rect.h = h;
    SDL_Rect src_rect;
    src_rect.x = x1;
    src_rect.y = y1;
    src_rect.w = w;
    src_rect.h = h;

    SDL_Point center_pos = frame.getAnchor();
    float angle = 0;
    SDL_RenderCopyEx(graphics.getRenderer(),
                     frame.getImage(),
                     &src_rect,
                     &dest_rect,
                     angle,
                     &center_pos,
                     (flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE)
    );
}
