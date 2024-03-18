#include <iostream>
#include "texture.hpp"
using namespace std;

Texture::Texture()
{
    m_texture = NULL;
    m_width = 0;
    m_height = 0;
}

Texture::~Texture()
{
    Free();
}

bool Texture::LoadFromFile(SDL_Renderer *renderer, string path)
{
    Free();

    // load image from path
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        cout << "Could not load image at " << path;
        cout << ": " << IMG_GetError() << endl;
        return false;
    }
    // color key image
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

    // create texture from pixels
    m_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (m_texture == NULL)
    {
        cout << "Could not create texture at " << path;
        cout << ": " << SDL_GetError() << endl;
        return false;
    }
    m_width = loaded_surface->w;
    m_height = loaded_surface->h;

    SDL_FreeSurface(loaded_surface);
    return true;
}

bool Texture::LoadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, string texture_text, SDL_Color text_color)
{
    Free();

    SDL_Surface *text_surface = TTF_RenderText_Solid(font, texture_text.c_str(), text_color);
    if (text_surface == NULL)
    {
        cout << "Could not render text surface: " << TTF_GetError() << endl;
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (m_texture == NULL)
    {
        cout << "Could not create texture from rendered text: " << SDL_GetError() << endl;
        return false;
    }
    m_width = text_surface->w;
    m_height = text_surface->h;

    // SDL_FreeSurface(text_surface);
    return true;
}

void Texture::Free()
{
    // free texture if it exists
    if (m_texture != NULL)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}

void Texture::Render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
    // set render space
    SDL_Rect render_quad = {x, y, m_width, m_height};

    // set clip rendering dimensions
    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopy(renderer, m_texture, clip, &render_quad);
}