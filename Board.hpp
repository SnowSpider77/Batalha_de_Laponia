#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Tile.hpp"

class Board {
private:
    static const int SIZE = 12;
    std::vector<std::vector<Tile>> board;

public:
    Board();

    void displayBoard() const;

    Tile& getTile(int x, int y);

    void setTileState(int x, int y, char state);
};

#endif