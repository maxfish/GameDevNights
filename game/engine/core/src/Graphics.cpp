#include <SDL2/SDL_image.h>
#include <engine/core/include/Graphics.h>

Graphics::Graphics(const char *window_title, int screen_width, int screen_height) {
    SDL_CreateWindowAndRenderer(screen_width, screen_height, 0, &_window, &_renderer);
    SDL_SetWindowTitle(_window, window_title);
}

Graphics::~Graphics() {
    SDL_DestroyWindow(_window);
}

SDL_Texture *Graphics::loadImage(const std::string &filePath) {
    if (_textures.count(filePath) == 0) {
        auto surface = IMG_LoadTexture(_renderer, filePath.c_str());
        if (surface == nullptr) {
            SDL_Log("Cannot load image '%s'!", filePath.c_str());
        } else {
            SDL_Log("Image '%s' loaded.", filePath.c_str());
        }
        _textures[filePath] = surface;
    }

    return _textures[filePath];
}

SDL_Texture *Graphics::loadTexture(const std::string &filePath) {
    auto texture = IMG_LoadTexture(_renderer, filePath.c_str());
    if (texture == nullptr) {
        SDL_Log("Cannot load texture '%s'!", filePath.c_str());
    } else {
        SDL_Log("Texture '%s' loaded.", filePath.c_str());
    }
    return texture;
}

void Graphics::blitTexture(SDL_Texture *texture, SDL_Rect *sourceRectangle,
                           SDL_Rect *destinationRectangle) {

    SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
    SDL_RenderPresent(_renderer);
}

void Graphics::clear(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    SDL_SetRenderDrawColor(_renderer, red, green, blue, alpha);
    SDL_RenderClear(_renderer);
}

SDL_Renderer *Graphics::getRenderer() const {
    return _renderer;
}

SDL_Window *Graphics::getWindow() const {
    return _window;
}
