#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {

public:

    Graphics(int screen_width, int screen_height);

    ~Graphics();

    SDL_Texture *loadImage(const std::string &filePath);

    void blitTexture(SDL_Texture *texture, SDL_Rect *sourceRectangle,
                     SDL_Rect *destinationRectangle);

    void flip();

    void clear();

    SDL_Renderer *getRenderer() const;

    SDL_Window *getWindow() const;

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    std::map<std::string, SDL_Texture *> _spriteSheets;

};



