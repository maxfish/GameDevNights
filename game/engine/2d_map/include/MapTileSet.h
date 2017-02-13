//
// Created by max on 12/02/17.
//

#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <engine/core/include/Graphics.h>

using namespace std;
class Map;

class MapTileSet {
    friend class Map;

    static const unsigned GID_MASK = 0x0FFFFFFF;

    static const unsigned FLAG_FLIPPED_HORIZONTALLY = 0x80000000;
    static const unsigned FLAG_FLIPPED_VERTICALLY = 0x40000000;
    static const unsigned FLAG_FLIPPED_DIAGONALLY = 0x20000000;

public:
    MapTileSet(Map *map);

    void drawTile(Graphics *graphics, Uint32 gid, int x, int y);

protected:
    Map *_map;

    string _name;
    string _image;
    SDL_Texture *_image_data;
    Uint16 _image_width;
    Uint16 _image_height;

    Uint16 _first_gid;
//    Uint16 _last_gid;
    Uint16 _tiles_count;
    Uint16 _tiles_on_a_row;
    Uint8 _tile_width;
    Uint8 _tile_height;
    Uint8 _margin;
    Uint8 _spacing;
};
