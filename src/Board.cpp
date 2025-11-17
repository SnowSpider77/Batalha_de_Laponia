#include "Board.hpp"
#include <iostream>

Board::Board(int width, int height)
    : width(width + 2), height(height + 2)
{
    board.resize(this->width, std::vector<Tile>());
    
    for (int x = 0; x < this->width; x++) {
        board[x].reserve(this->height);

        for (int y = this->height - 1; y >= 0; y--) {
            Tile::Type t;

            if (x == 0 || x == this->width - 1 || y == 0 || y == this->height - 1)
                t = Tile::Type::Wall;
            else if (y == this->height / 2|| (this->height % 2 == 0 && y == this->height / 2 - 1))
                t = Tile::Type::River;
            else
                t = Tile::Type::Floor;
            board[x].emplace_back(x, y, t);
        }
    }
}


void Board::displayBoard() const {
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            std::cout << board[x][y];
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
    return p.x >= 0 && p.x < width &&
           p.y >= 0 && p.y < height;
}

bool Board::isEmpty(Position p) const {
    return (getTile(p).getOccupant() == nullptr);
}

bool Board::isWalkable(Position p) const {
    if (!inBounds(p)) return false;
    return (getTile(p).getType() == Tile::Type::Floor && isEmpty(p));
}

Troop * Board::getTroop(Position p) const {
    if(!inBounds(p)) return nullptr;
    return getTile(p).getOccupant();
}

void Board::placeTroop(Position p, Troop * t) {
    if (!isWalkable(p)) return;
    getTile(p).setOccupant(t);
}

void Board::removeTroop(Position p) {
    if (!inBounds(p)) return;
    Tile& tile = getTile(p);
    Troop * t = tile.getOccupant();
    if (t) {
        delete t;
        tile.setOccupant(nullptr);
    }
}

void Board::moveTroop(Position from, Position to) {
    if (!inBounds(to) || !inBounds(from)) return;
    Tile& tileTo = getTile(to);
    if (tileTo.getOccupant() != nullptr) return;
    Tile& tileFrom = getTile(from);
    Troop * t = tileFrom.getOccupant();
    if (!t) return;
    tileTo.setOccupant(t);
    tileFrom.setOccupant(nullptr);
}

int Board::countTroopsOwner(Troop::Player owner){
    int n = 0;
    for (int x = 1; x < width - 1; x++)
        for (int y = 1; y < height - 1; y++){
            Troop * t = getTroop({x, y});
            if (!t) continue;
            if (t->getOwner() == owner) n++;
        }

    return n;
}

void Board::clear() {
    for (int x = 1; x < width - 1; x++)
        for (int y = 1; y < height - 1; y++)
            removeTroop({x, y});
}