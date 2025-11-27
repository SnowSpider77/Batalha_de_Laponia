#include "Troop.hpp"
#include "Board.hpp"

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

// Função auxiliar para imprimir o "nome" do jogador
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

// Complementa o construtor de troop, especificando o tipo e o símbolo de cada tropa
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

// Atque do fuzileiro, funciona de forma recursiva, iterando sobre as casas e viajando na direção y
// Para quando encontrar uma tropa e destruí-la ou quando sair dos limites do tabuleiro
// Nota: nenhuma função de ataque impede friendly fire  
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

// Ataque do flanco, funciona de forma recursiva, movendo-se em ambas direções
// Para quando encontrar uma tropa e destruí-la ou quando sair dos limites do tabuleiro
void DiagonalTroop::attack(Board& board, Position p, int d) {
    // d é a direção, 1 para esquerda e 2 para direita
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

// Ataque do sniper, funciona de forma recursiva, movendo-se em ambas direções ou reto, a escolha do jogador
// Para apenas quando sair dos limites do tabuleiro, destruindo todas as tropas no caminho
void SpecialWallTroop::attack(Board& board, Position p, int d) {
    // d é a direção, -1 para esquerda, 0 para reto, 1 para direita
    if (p.x == -1 && p.y == -1) p = getPos();
    p.y += (getOwner() == Player::North ? -1 : 1 );
    p.x += d;
    if (!board.inBounds(p)) return;
    Troop * t = board.getTroop(p);
    if (t != nullptr) board.removeTroop(p);
    attack(board, p, d);
}

// Ataque do morteiro
// Funciona varrendo uma matriz 3x3 numa posição escolhida e eliminando todas as tropas na região
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