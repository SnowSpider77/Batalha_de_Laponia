#include "Tile.hpp"

Tile::Tile(int x, int y, char state) 
    : x(x), y(y), state(state) {}

char Tile::getState() const {
    return state;
}

void Tile::setState(char newState) {
    state = newState;
}

int Tile::getType() const {
    return state;
}

void Tile::setType(Type newType) {
    type = newType;
}

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}