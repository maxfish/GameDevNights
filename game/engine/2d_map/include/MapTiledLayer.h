//
// Created by max on 12/02/17.
//

#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "MapLayer.h"
#include <zlib.h>
#include <vector>
#include <engine/2d_map/include/Map.h>

class MapTiledLayer : public MapLayer {
    friend class Map;

public:
    MapTiledLayer(Map *map);

    void setData(vector<Uint32> *data);

    void draw(Graphics *graphics);

protected:
    std::vector<Uint32> *_tiles;
};