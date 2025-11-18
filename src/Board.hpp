#pragma once

#include <vector>
#include "Tile.hpp"

class Board {
private:
    int width;
    int height;
    std::vector<std::vector<Tile>> board;

public:
    Board(int width, int height);

    void displayBoard() const;

    Tile& getTile(Position p);
    Tile const& getTile(Position p) const;

    int getHeight() const;
    int getWidth() const;

    bool inBounds(Position P) const;
    bool isEmpty(Position p) const;
    bool isWalkable(Position p) const;

    Troop * getTroop(Position p) const;
    void placeTroop(Position p, Troop * t);
    void removeTroop(Position p);
    void moveTroop(Position from, Position to);
    int countTroopsOwner(Troop::Player owner);

    void clear();
};