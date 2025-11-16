#include "Troop.hpp"

Troop::Troop(Player owner, int x, int y, TroopType type) : owner(owner), pos{x,y}, type(type) {}

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

Troop::Player Troop::getOwner() const{
    return owner;
}

char Troop::getSymbol() const{
    return symbol;
}