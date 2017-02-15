//
// Created by max on 12/02/17.
//

#include <engine/2d_map/include/MapTileSet.h>


MapTileSet::MapTileSet(Map *map) {
    _map = map;
}

void MapTileSet::drawTile(Graphics *graphics, Uint32 gid, int x, int y) {
    bool flipped_horizontally = (bool) (gid & FLAG_FLIPPED_HORIZONTALLY);
    bool flipped_vertically = (bool) (gid & FLAG_FLIPPED_VERTICALLY);
    bool flipped_diagonally = (bool) (gid & FLAG_FLIPPED_DIAGONALLY);

    // Clear the flags
    gid &= GID_MASK;
    Uint32 relative_index = gid - _first_gid;

    int tile_x = relative_index % _tiles_on_a_row;
    int tile_y = relative_index / _tiles_on_a_row;
//    SDL_Log("gid:%d x:%d y:%d", gid, tile_x, tile_y);
    SDL_Rect source_rect = {tile_x * _tile_width, tile_y * _tile_height, _tile_width, _tile_height};
    SDL_Rect dest_rect = {x, y, _tile_width, _tile_height};
    SDL_Point anchor = {_tile_width / 2, 0};
    SDL_RenderCopyEx(graphics->getRenderer(), _image_data, &source_rect, &dest_rect, 0, &anchor,
                     flipped_horizontally ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
