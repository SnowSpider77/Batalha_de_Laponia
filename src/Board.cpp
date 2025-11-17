#include "Board.hpp"
#include <iostream>

Board::Board(int width, int height) : width(width), height(height) {
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

Tile& Board::getTile(Position p) {
    return board[p.x][p.y];
}

Tile const& Board::getTile(Position p) const {
    return board[p.x][p.y];
}

bool Board::inBounds(Position p) const {
    return (getTile(p).getType() != Tile::Type::Wall);
}

bool Board::isEmpty(Position p) const {
    return (getTile(p).getOccupant() == nullptr);
}

bool Board::isWalkable(Position p) const {
    return (getTile(p).getType() == Tile::Type::Floor && isEmpty(p));
}

Troop * Board::getTroop(Position p) const {
    return getTile(p).getOccupant();
}

void Board::placeTroop(Position p, Troop * t) {
    getTile(p).setOccupant(t);
}

void Board::removeTroop(Position p) {
    Tile tile = getTile(p);
    Troop * t = tile.getOccupant();
    if (t) {
        delete t;
        tile.setOccupant(nullptr);
    }
}

void Board::moveTroop(Position from, Position to) {
    Tile tileTo = getTile(to);
    if (tileTo.getOccupant() != nullptr) return;
    Tile tileFrom = getTile(from);
    Troop * t = tileFrom.getOccupant();
    if (!t) return;
    tileTo.setOccupant(t);
    tileFrom.setOccupant(nullptr);
}

void Board::clear() {
    for (int x = 1; x < width - 1; x++)
        for (int y = 1; y < height - 1; y++)
            removeTroop({x, y});
}