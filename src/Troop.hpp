#ifndef TROOP_H
#define TROOP_H

#include<vector>

class Board;

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

    virtual void attack() = 0;
    virtual std::vector<Position> getLegalMoves(Board const& board) const = 0;
    virtual std::vector<Position> getLegalTargets(Board const& board) const = 0;

    char getSymbol() const;
};

#endif