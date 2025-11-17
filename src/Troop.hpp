#pragma once

#include<vector>
#include<stdexcept>

class Board;

struct Position{
    int x;
    int y;
};

class Troop {
public:
    enum class Player {North, South};
    enum class TroopType { Axial, Diagonal, SpecialWall, SpecialBomb};

private:
    Position pos;
    Player owner;
    TroopType type;
    char symbol;

public:
    Troop(Player owner, int x, int y);
    virtual ~Troop() = default;

    Position getPos() const;
    void moveTo(int x, int y);

    Player getOwner() const;

    virtual void attack(Board& board, Position p) {
        throw std::runtime_error("This troop requires more information for the attack");
    }
    virtual void attack(Board& board, Position p, int d) {
        throw std::runtime_error("This troop type does not support directional attack");
    }

    TroopType getType() const;
    static std::string typeToString(Player player);
    void setType(TroopType t);

    char getSymbol() const;
    void setSymbol(char c);
};


class AxialTroop : public Troop {
public:
    
    AxialTroop(Player owner, int x, int y);
    ~AxialTroop() = default;

    void attack(Board& board, Position p) override;
};

class DiagonalTroop : public Troop {
public:
    DiagonalTroop(Player owner, int x, int y);
    ~DiagonalTroop() = default;

    void attack(Board& board, Position p, int d) override;
};

class SpecialWallTroop : public Troop {
public:
    SpecialWallTroop(Player owner, int x, int y);
    ~SpecialWallTroop() = default;

    void attack(Board& board, Position p, int d) override;
};


class SpecialBombTroop : public Troop {
public:
    SpecialBombTroop(Player owner, int x, int y);
    ~SpecialBombTroop() = default;

    void attack(Board& board, Position p) override;
};