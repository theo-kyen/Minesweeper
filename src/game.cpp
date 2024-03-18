#include <iostream>
#include <sstream>
#include "game.hpp"
using namespace std;

Game::Game()
{
    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Could not initialize SDL: " << SDL_GetError() << endl;
    }
    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "Could not initialize SDL_IMG: " << IMG_GetError() << endl;
    }
    if (TTF_Init() < 0)
    {
        cout << "Could not initialize SDL_TTF: " << TTF_GetError() << endl;
    }

    // create window and renderer
    window = SDL_CreateWindow("Minesweeper - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Could not create window: " << SDL_GetError() << endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        cout << "Could not create renderer: " << SDL_GetError() << endl;
    }

    // open font
    font = TTF_OpenFont("assets/font.ttf", 30);
    if (font == NULL)
    {
        cout << "Could not load font: " << TTF_GetError() << endl;
    }

    board = new Board(NUM_MINES);
}

void Game::Run()
{
    SDL_Event event;
    bool quit = false;

    while (!quit)
    {
        int mouse_x, mouse_y;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_MOUSEBUTTONUP && !board->IsGameOver(NUM_MINES))
            {
                // get mouse coordinates, ensure valid click
                SDL_GetMouseState(&mouse_x, &mouse_y);
                if (mouse_y < 120)
                    continue;

                // get click type, update board
                State state;
                SDL_MouseButtonEvent b = event.button;
                if (b.button == SDL_BUTTON_LEFT)
                    state = State::Uncovered;
                else if (b.button == SDL_BUTTON_RIGHT)
                    state = State::Flagged;

                board->ChangeState(state, mouse_x, mouse_y);
            }
        }

        // update screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        board->Render(renderer);
        if (board->IsGameOver(NUM_MINES))
            RenderResultText();
        else
        {
            finish_time = SDL_GetTicks64() - start_time;
            RenderGameText();
        }

        SDL_RenderPresent(renderer);
    }

    Close();
}

void Game::Close()
{
    free(board);

    flag_display.Free();
    time_display.Free();
    result_display.Free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_CloseFont(font);
    font = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::RenderGameText()
{
    stringstream flag_text, time_text;

    flag_text << "Flags Used: " << NUM_MINES - board->GetNumberFlaggedTiles();
    flag_display.LoadFromRenderedText(renderer, font, flag_text.str(), SDL_Color{255, 255, 255});
    time_text << "Time: " << (SDL_GetTicks64() - start_time) / 1000;
    time_display.LoadFromRenderedText(renderer, font, time_text.str(), SDL_Color{255, 255, 255});

    flag_display.Render(renderer, 100, 50);
    time_display.Render(renderer, 400, 50);
}

void Game::RenderResultText()
{
    stringstream result_text, time_text;

    result_text << (board->DidPlayerWin(NUM_MINES) ? "You Win!" : "You Lose!");
    result_display.LoadFromRenderedText(renderer, font, result_text.str(), SDL_Color{255, 255, 255});
    time_text << "Time: " << finish_time / 1000;
    time_display.LoadFromRenderedText(renderer, font, time_text.str(), SDL_Color{255, 255, 255});

    result_display.Render(renderer, 225, 20);
    time_display.Render(renderer, 230, 50);
}
