#include "board.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

Board::Board(int mines) : m_mines(mines)
{
    Init();
}

void Board::Init()
{
    memset(m_grid, 0, (ROWS * COLS) * sizeof(int));
    if (!m_tiles.empty())
        m_tiles.clear();

    int mines_left = m_mines;
    int row, col;

    // generate mine tiles at random positions
    srand(time(NULL));
    while (mines_left > 0)
    {
        row = rand() % ROWS;
        col = rand() % COLS;
        while (m_grid[row][col] == 9)
        {
            row = rand() % ROWS;
            col = rand() % COLS;
        }

        m_grid[row][col] = 9;
        m_tiles.push_back(Tile(row, col, Type::Mine));

        if (row - 1 >= 0 && col - 1 >= 0 && m_grid[row - 1][col - 1] != 9)
            m_grid[row - 1][col - 1]++;
        if (row - 1 >= 0 && m_grid[row - 1][col] != 9)
            m_grid[row - 1][col]++;
        if (row - 1 >= 0 && col + 1 < COLS && m_grid[row - 1][col + 1] != 9)
            m_grid[row - 1][col + 1]++;
        if (col - 1 >= 0 && m_grid[row][col - 1] != 9)
            m_grid[row][col - 1]++;
        if (col + 1 < COLS && m_grid[row][col + 1] != 9)
            m_grid[row][col + 1]++;
        if (row + 1 < ROWS && col - 1 >= 0 && m_grid[row + 1][col - 1] != 9)
            m_grid[row + 1][col - 1]++;
        if (row + 1 < ROWS && m_grid[row + 1][col] != 9)
            m_grid[row + 1][col]++;
        if (row + 1 < ROWS && col + 1 < COLS && m_grid[row + 1][col + 1] != 9)
            m_grid[row + 1][col + 1]++;

        mines_left--;
    }

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (m_grid[row][col] != 9)
            {
                Tile tile(row, col, Type::Grass);
                tile.SetAdjacentMines(m_grid[row][col]);
                m_tiles.push_back(tile);
            }
        }
    }
}

void Board::ChangeState(State state, int mouse_x, int mouse_y)
{
    Tile &tile = GetTile(mouse_x, mouse_y);
    tile.ChangeState(state);
}

int Board::GetNumberFlaggedTiles()
{
    int num_flagged = 0;

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            Tile tile = GetTile(row, col, false);
            if (tile.GetState() == State::Flagged)
                num_flagged++;
        }
    }

    return num_flagged;
}

void Board::Render(SDL_Renderer *renderer)
{
    for (Tile &tile : m_tiles)
        tile.Render(renderer);
}

bool Board::IsGameOver(int num_mines)
{
    return GetUncoveredGrassTiles() == -1 || DidPlayerWin(num_mines);
}

bool Board::DidPlayerWin(int num_mines)
{
    return (ROWS * COLS) - GetUncoveredGrassTiles() == num_mines;
}

Tile &Board::GetTile(int x, int y, bool mouse_coords)
{
    int row, col;
    if (mouse_coords)
    {
        row = x / Tile::SIZE;
        col = (y - (Tile::SIZE * 2)) / Tile::SIZE;
    }
    else
    {
        row = x;
        col = y;
    }

    for (Tile &tile : m_tiles)
    {
        if (tile.GetRow() == row && tile.GetCol() == col)
            return tile;
    }
}

int Board::GetUncoveredGrassTiles()
{
    int num_uncovered = 0;

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            Tile &tile = GetTile(row, col, false);
            if (tile.GetState() == State::Uncovered)
            {
                if (tile.GetType() == Type::Mine)
                    return -1;
                else
                    num_uncovered++;
            }
        }
    }

    return num_uncovered;
}
