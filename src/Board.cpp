#include "Board.hpp"
#include <iostream>

Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < SIZE; j++) {
            row.emplace_back(i, j);
        }
        board.push_back(row);
    }
}

void Board::displayBoard() const {
    for (const std::vector<Tile>& row : board) {
        for (const Tile& tile : row) {
            std::cout << tile.getState() << ' ';
        }
        std::cout << '\n';
    }
}

Tile& Board::getTile(int x, int y) {
    return board[x][y];
}

void Board::setTileState(int x, int y, char state) {
    board[x][y].setState(state);
}
