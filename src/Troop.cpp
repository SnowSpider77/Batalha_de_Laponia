#include "Troop.hpp"
#include "Board.hpp" // ajuste se seu arquivo Board tiver outro nome

Troop::Troop(Player owner, int x, int y)
    : owner(owner), pos{x,y} {}

Position Troop::getPos() const {
    return pos;
}

void Troop::moveTo(int x, int y) {
    pos.x = x;
    pos.y = y;
}

Troop::Player Troop::getOwner() const {
    return owner;
}

Troop::TroopType Troop::getType() const {
    return type;
}

std::string Troop::typeToString(Player player) {
    return (player == Player::North ? "Norte" : "Sul");
}

void Troop::setType(TroopType t) {
    type = t;
}

char Troop::getSymbol() const {
    if (symbol) return symbol;
    else return ' ';
}

void Troop::setSymbol(char c) {
    symbol = c;
}

AxialTroop::AxialTroop(Player owner, int x, int y) : Troop(owner, x, y){
    setType(Troop::TroopType::Axial);
    setSymbol('1');
}
DiagonalTroop::DiagonalTroop(Player owner, int x, int y) : Troop(owner, x, y) {
    setType(Troop::TroopType::Diagonal);
    setSymbol('2');
}
SpecialWallTroop::SpecialWallTroop(Player owner, int x, int y) : Troop(owner, x, y) {
    setType(Troop::TroopType::SpecialWall);
    setSymbol('#');
}
SpecialBombTroop::SpecialBombTroop(Player owner, int x, int y) : Troop(owner, x, y) {
    setType(Troop::TroopType::SpecialBomb);
    setSymbol('@');
}


void AxialTroop::attack(Board& board, Position p) {
    if (p.x == -1 && p.y == -1) p = getPos();
    p.y += (getOwner() == Player::North ? -1 : 1 );
    if (!board.inBounds(p)) return;
    Troop * t = board.getTroop(p);
    if (t != nullptr){
        board.removeTroop(p);
        return;
    }
    attack(board, p);
}

void DiagonalTroop::attack(Board& board, Position p, int d) {
    // d is direction, 1 for left 2 for right
    if (p.x == -1 && p.y == -1) p = getPos();
    p.y += (getOwner() == Player::North ? -1 : 1 );
    p.x += (d == 1 ? -1 : 1);
    if (!board.inBounds(p)) return;
    Troop * t = board.getTroop(p);
    if (t != nullptr){
        board.removeTroop(p);
    }
    attack(board, p, d);
}

void SpecialWallTroop::attack(Board& board, Position p, int d) {
    // d in direction, -1 for left, 0 for straight, 1 for right
    if (p.x == -1 && p.y == -1) p = getPos();
    p.y += (getOwner() == Player::North ? -1 : 1 );
    p.x += d;
    if (!board.inBounds(p)) return;
    Troop * t = board.getTroop(p);
    if (t != nullptr) board.removeTroop(p);
    attack(board, p, d);
}

void SpecialBombTroop::attack(Board& board, Position p){
    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            Position pow = {p.x + dx, p.y + dy};
            if (!board.inBounds(pow)) continue;
            if(board.getTile(pow).getOccupant())
                board.removeTroop(pow);
        }
    }
}