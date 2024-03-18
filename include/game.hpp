#pragma once

#include "board.hpp"

class Game
{
public:
    Game();
    void Run();
private:
    void Close();
    void RenderGameText();
    void RenderResultText();

    const int SCREEN_SIZE = 600;
    const int NUM_MINES = 10;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    Texture flag_display;
    Texture time_display;
    Texture result_display;

    Board *board;
    Uint32 start_time = SDL_GetTicks64();
    Uint32 finish_time;
};