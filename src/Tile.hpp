#pragma once

#include "Troop.hpp"

#include <sstream>

class Tile {
public:
    // enum com os tipos de casa, se é chão, rio ou parede (fora dos limites do tabuleiro)
    enum class Type { Floor, Wall, River };

private:
    int x, y;
    Type type;
    Troop * occupant; // Tropa que ocupa a casa do tabuleiro

public:
    Tile(int x, int y, Type type);

    int getX() const;
    int getY() const;
    Type getType() const;
    Troop * getOccupant() const;
    void setOccupant(Troop * t);

    // Sobrecarga para facilitar a impressão do tabuleiro
    friend std::ostream& operator<<(std::ostream& os, Tile const& tile);
};