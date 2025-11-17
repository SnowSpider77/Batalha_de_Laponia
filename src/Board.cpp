#include "Board.hpp"
#include <iostream>

Board::Board() {
    board.resize(height, std::vector<Tile>());
    for (int y = 0; y < height; y++) {
        board[y].reserve(width);

        for (int x = 0; x < width; x++) {
            Tile::Type t;

            if (x == 0 || x == width-1 || y == 0 || y == height-1)
                t = Tile::Type::Wall;
            else if (y == 5 || y == 6)
                t = Tile::Type::River;
            else
                t = Tile::Type::Floor;

            board[y].emplace_back(x, y, t);
        }
    }
}

void Board::displayBoard() const {
    for (const std::vector<Tile>& row : board) {
        for (const Tile& tile : row) {
            std::cout << tile;
        }
        std::cout << '\n';
    }
}

Tile& Board::getTile(int x, int y) {
    return board[x][y];
}