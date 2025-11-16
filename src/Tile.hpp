#ifndef TILE_H
#define TILE_H

#include "Troop.hpp"

#include <sstream>

class Tile {
public:
    enum class Type { Floor, Wall, River };

private:
    int x, y;
    Type type;
    Troop * occupant;

public:
    Tile(int x, int y, Type type);

    int getX() const;
    int getY() const;
    Type getType() const;
    Troop * getOccupant() const;

    friend std::ostream& operator<<(std::ostream& os, Tile const& tile);
};

#endif