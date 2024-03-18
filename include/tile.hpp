#pragma once

#include "texture.hpp"

// represents the tile's type
enum Type
{
    Grass,
    Mine
};
// the tile's current state
enum State
{
    Covered,
    Uncovered,
    Flagged
};

class Tile
{
public:
    static const int SIZE = 60;

    Tile(int row, int col, Type type, State state) : m_row(row), m_col(col), m_adj_mines(0), m_type(type), m_state(state) {}
    Tile(int row, int col, Type type) : Tile(row, col, type, State::Covered) {}
    Tile() : m_row(-1), m_col(-1) {}

    int GetRow() { return m_row; }
    int GetCol() { return m_col; }
    int GetAdjacentMines() { return m_adj_mines; }
    int GetType() { return m_type; }
    int GetState() { return m_state; }

    void SetAdjacentMines(int mines) { m_adj_mines = mines; }

    // changes the state of the tile from Covered to the given state
    void ChangeState(State state);
    // renders the tile onto the screen
    // if uncovered, displays either the number of adjacent mines or the mine itself
    void Render(SDL_Renderer *renderer);

private:
    int m_row, m_col; // the tile's coordinates
    int m_adj_mines;
    Texture m_texture;
    Type m_type;
    State m_state;
};