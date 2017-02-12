//
// Created by max on 12/02/17.
//

#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <engine/core/include/Graphics.h>

using namespace std;

class Map;

enum MapLayerType {
    MapLayerType_Unknown = -1,
    MapLayerType_Tiles,
    MapLayerType_Objects
};

class MapLayer {
    friend class Map;

public:
    MapLayer(Map *map);

    virtual void draw(Graphics *graphics);

protected:
    Map *_map;

    string _name;
    Uint16 _width;
    Uint16 _height;
    float _opacity;
    int _offset_x;
    int _offset_y;
    bool _visible;
};