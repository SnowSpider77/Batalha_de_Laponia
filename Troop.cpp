#include "Troop.hpp"

Troop::Troop(int x, int y) : pos{x, y} {}

Position Troop::getPos() const {
    return pos;
}

void Troop::moveTo(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void Troop::moveDelta(int dx, int dy){
    pos.x += dx;
    pos.y += dy;
}