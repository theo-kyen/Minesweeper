#include "tile.hpp"
#include <iostream>
using namespace std;

void Tile::ChangeState(State state)
{
    if (m_state == State::Covered)
        m_state = state;
    else if (m_state == State::Flagged && state == State::Flagged)
        m_state = State::Covered;
}

void Tile::Render(SDL_Renderer *renderer)
{
    SDL_Rect rect = {m_row * SIZE, (m_col + 2) * SIZE, SIZE, SIZE};

    // create default checkerboard pattern (all tiles covered)
    if ((m_row + m_col) % 2 == 0)
        SDL_SetRenderDrawColor(renderer, 20, 70, 10, 255);
    else
        SDL_SetRenderDrawColor(renderer, 20, 100, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    switch (m_state)
    {
    case Uncovered:
    {
        // create uncovered checkerboard pattern
        if ((m_row + m_col) % 2 == 0)
            SDL_SetRenderDrawColor(renderer, 165, 130, 35, 255);
        else
            SDL_SetRenderDrawColor(renderer, 200, 165, 65, 255);
        SDL_RenderFillRect(renderer, &rect);

        if (m_type == Type::Grass)
        {
            // display number of adjacent mines
            if (m_adj_mines > 0 && m_adj_mines < 9)
            {
                string path = "assets/" + to_string(m_adj_mines) + ".png";
                m_texture.LoadFromFile(renderer, path);
                m_texture.Render(renderer, m_row * SIZE, (m_col + 2) * SIZE);
            }
        }
        else
        {
            // draw mine
            SDL_Rect mine = {(m_row * SIZE) + (SIZE / 4), ((m_col + 2) * SIZE) + (SIZE / 4), SIZE / 2, SIZE / 2};
            SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
            SDL_RenderFillRect(renderer, &mine);
        }
        break;
    }
    case Flagged:
        // draw flag
        SDL_Rect flag = {(m_row * SIZE) + (SIZE / 6), ((m_col + 2) * SIZE) + (SIZE / 6), int(SIZE / 1.5), SIZE / 3};
        SDL_Rect pole = {(m_row * SIZE) + (SIZE / 6), ((m_col + 2) * SIZE) + (SIZE / 6), SIZE / 6, int(SIZE / 1.5)};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &flag);
        SDL_RenderFillRect(renderer, &pole);
        break;
    }
}