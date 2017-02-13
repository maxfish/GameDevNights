//
// Created by max on 12/02/17.
//

#pragma once

#include <vector>
#include "MapLayer.h"
#include "MapTileSet.h"
#include <engine/core/include/Graphics.h>

using namespace std;

enum {
//    "orthogonal", "isometric", "staggered" (since 0.9) and "hexagonal"
} MapOrientation;

enum {
//right-down (the default), right-up, left-down and left-up
} MapRenderOrder;

class Map {

public:
    Map(Graphics &graphics);

    void setViewport(SDL_Rect view_port);

    SDL_Rect getViewport();

    void setOffset(SDL_Point offset);

    SDL_Point getOffset();

    Uint8 getTileWidth();

    Uint8 getTileHeight();

    void draw();

    MapTileSet *tileSetFromGid(Uint32 global_index);

    void loadFromJSON(string file_path, string file_name);

protected:
    SDL_Rect _viewport;
    SDL_Point _offset;

    Uint16 _width;
    Uint16 _height;
    Uint8 _tile_width;
    Uint8 _tile_height;
    Uint8 _next_object_id;
//    MapOrientation _orientation;
//    MapRenderOrder _render_order;

    vector<MapLayer *> *_layers;
    vector<MapTileSet *> *_tile_sets;

private:
    Graphics *_graphics;
};

//"version":1,
//"width":24,
//"height":20,
//"tilewidth":32,
//"tileheight":32,
//"nextobjectid":8,
//"orientation":"orthogonal",
//"renderorder":"right-down",