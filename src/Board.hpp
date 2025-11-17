#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Tile.hpp"

class Board {
private:
    static const int width = 12;
    static const int height = 12;
    std::vector<std::vector<Tile>> board;

public:
    Board();

    void displayBoard() const;

    Tile& getTile(int x, int y);

    Tile& getTile(Position p);
    Tile const& getTile(Position p) const;

    bool inBounds(Position P) const;
    bool isEmpty(Position p) const;
    bool isWalkable(Position p) const;
    Troop * getTroop(Position p) const;

    void placeTroop(Position p, Troop * t);
    void removeTroop(Position p);
    void moveTroop(Position from, Position to);
    void moveTroopDelta(Position from, Position delta);
};

#endif