#pragma once

#include "board.hpp"

class Game
{
public:
    Game();
    void Run();

private:
    const int SCREEN_SIZE = 600;
    const int NUM_MINES = 10;
    const SDL_Color COLOR_WHITE{255, 255, 255};

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    Texture restart_display;
    Texture quit_display;
    Texture flag_display;
    Texture time_display;
    Texture result_display;

    Board *board;
    Uint32 start_time = SDL_GetTicks64();
    Uint32 finish_time;

    void Restart();
    void RenderOptionsText();
    void RenderGameText();
    void RenderResultText();
    void Close();
};