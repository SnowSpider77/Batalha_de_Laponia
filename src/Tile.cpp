#include "Tile.hpp"

Tile::Tile(int x, int y, Type type) : x(x), y(y), type(type), occupant(nullptr) {}

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}

Tile::Type Tile::getType() const {
    return type;
}

Troop * Tile::getOccupant() const {
    return occupant;
}

void Tile::setOccupant(Troop * t) {
    occupant = t;
}

std::string typeToString(Tile::Type type) {
    switch (type) {
        case Tile::Type::Floor: return "[ ]";
        case Tile::Type::Wall:  return "   ";
        case Tile::Type::River: return "~~~";
    }
    return " ? ";
}

std::ostream& operator<<(std::ostream& os, Tile const& tile) {
    std::string out = typeToString(tile.getType());

    if (tile.getType() == Tile::Type::Floor and tile.occupant != nullptr) 
        out.replace(1, 1, 1, tile.occupant->getSymbol());

    os << out;
    return os;
}