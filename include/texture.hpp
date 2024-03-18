#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// texture wrapper class
class Texture
{
public:
    Texture();
    ~Texture();

    // gets image dimensions
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }

    // loads image from the given path
    bool LoadFromFile(SDL_Renderer *renderer, std::string path);
    // creates image from font string
    bool LoadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, std::string texture_text, SDL_Color text_color);
    // deallocates texture
    void Free();
    // renders texture at the given point
    void Render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL);

private:
    SDL_Texture *m_texture;
    int m_width, m_height;
};