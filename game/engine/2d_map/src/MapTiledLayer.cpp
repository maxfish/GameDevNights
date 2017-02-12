//
// Created by max on 12/02/17.
//

#include "engine/2d_map/include/MapTiledLayer.h"

MapTiledLayer::MapTiledLayer(Map *map) : MapLayer(map) {
}

void MapTiledLayer::setData(vector<Uint32> *data) {
    _tiles = data;
}

void MapTiledLayer::draw(Graphics *graphics) {
    if (!_visible) {
        return;
    }
    Uint8 tile_width = _map->getTileWidth();
    Uint8 tile_height = _map->getTileHeight();
    for (Uint8 y = 0; y < 20; y++) {
        for (Uint8 x = 0; x < 20; x++) {
            Uint32 gid = _tiles->at(x + y * _width);
            if (gid == 0) {
                continue;
            }
            MapTileSet *set = _map->tileSetFromGid(gid);
            set->drawTile(graphics, gid, x * tile_width, y * tile_height);
        }
    }
}
