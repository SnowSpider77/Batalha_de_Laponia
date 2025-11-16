#ifndef TROOP_H
#define TROOP_H

#include "Board.hpp"

struct Position{
    int x;
    int y;
};

class Troop {
public:
    enum class Player {P1, P2};
    enum class TroopType { Axial, Diagonal, SpecialWall, SpecialMine};

private:
    Position pos;
    Player owner;
    TroopType type;
    char symbol;

public:
    Troop(Player owner, int x, int y, TroopType type);
    virtual ~Troop() = default;

    Position getPos() const;
    void moveTo(int x, int y);
    void moveDelta(int dx, int dy);

    Player getOwner() const;

    virtual void attack();
    virtual std::vector<Position> getLegalMoves(Board const& board) const;
    virtual std::vector<Position> getLegalTargets(Board const& board) const;
};

#endif