#pragma once

#include "tile.hpp"
#include <vector>

class Board
{
public:
    Board(int mines);

    // changes the state of the tile at the given mouse coordinates
    void ChangeState(State state, int mouse_x, int mouse_y);
    // returns the number of flagged tiles
    int GetNumberFlaggedTiles();
    // renders the board's grid onto the screen
    void Render(SDL_Renderer *renderer);
    // returns true when the game is complete
    bool IsGameOver(int num_mines);
    // returns true if the player won
    bool DidPlayerWin(int num_mines);

private:
    static const int ROWS = 10;
    static const int COLS = 8;

    int m_mines; // number of mines in the game
    int m_grid[ROWS][COLS];
    Tile m_tiles[ROWS][COLS];

    // returns the tile at the given mouse coordinates
    Tile &GetTile(int x, int y);
    // returns the number of uncovered grass tiles
    int GetUncoveredGrassTiles();
};