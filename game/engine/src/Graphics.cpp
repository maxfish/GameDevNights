#include "graphics.h"
#include <SDL2/SDL_image.h>
#include "globals.h"

Graphics::Graphics(int screen_width, int screen_height) {
    SDL_CreateWindowAndRenderer(screen_width, screen_height, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "SDL Engine");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->_window);
}

SDL_Texture *Graphics::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0) {
        auto surface = IMG_Load(filePath.c_str());
        this->_spriteSheets[filePath] = SDL_CreateTextureFromSurface(this->_renderer, surface);
        SDL_FreeSurface(surface);
    }

    return this->_spriteSheets[filePath];
}

void Graphics::blitTexture(SDL_Texture *texture, SDL_Rect *sourceRectangle,
                           SDL_Rect *destinationRectangle) {

    SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);

}

void Graphics::flip() {
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
    SDL_RenderClear(this->_renderer);
    SDL_SetRenderDrawColor(this->_renderer, 168, 230, 255, 255);
}

SDL_Renderer *Graphics::getRenderer() const {
    return this->_renderer;
}

SDL_Window *Graphics::getWindow() const {
    return this->_window;
}
