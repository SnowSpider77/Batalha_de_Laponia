#include "Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game(int width, int height, int troopsPerPlayer, int specialTroopsPerPlayer)
: board(width, height),
  currentPlayer(Troop::Player::North),
  specialUsesNorth(4),
  specialUsesSouth(4),
  troopsPerPlayer(troopsPerPlayer),
  specialTroopsPerPlayer(specialTroopsPerPlayer)
{}

Board& Game::getBoard() {
    return board;
}

void Game::start() {
    cleanup();
    placementPhase();
    battleLoop();
}

bool Game::inBoard(int x, int y) const {
    return board.inBounds({x, y});
}

void Game::cleanup() {
    specialUsesNorth = 4;
    specialUsesSouth = 4;
    board.clear();
}

void Game::placementPhase() {
    std::cout << "Fase de posicionamento: cada jogador posiciona:\n- "
    << troopsPerPlayer << " tropas comuns;\n- "
    << specialTroopsPerPlayer << " tropas especiais." << std::endl;
    for (Troop::Player player : {Troop::Player::North, Troop::Player::South}) {
        std::cout << (player==Troop::Player::North ? "Posicionamento do Norte (#)" : "Posicionamento do Sul (@)") << std::endl;
        int placed = 0;
        int specialPlaced = 0;
        while (placed < troopsPerPlayer + specialTroopsPerPlayer) {
            board.displayBoard();
            std::cout << "Jogador do " << Troop::typeToString(player)
            << " posicione a tropa " << placed+1 << " (formato: tipo x y)" << std::endl;
            std::cout << "Tipo 1 = Fuzileiro\nTipo 2 = Flanco"
            << (specialPlaced < specialTroopsPerPlayer ? "\nTipo 3 = Especial" : "") << std::endl;
            int type, x, y;
            if (!(std::cin >> type >> x >> y)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Input invalido" << std::endl;
                continue;
            }
            if (!board.isWalkable({x,y})) {
                std::cout << "A tropa nao pode ser posicionada aqui" << std::endl;
                continue;
            }
            if(player == Troop::Player::North) {
                if (y < board.getHeight() / 2) {
                    std::cout << "A tropa do Norte deve ser posicionada no lado superior" << std::endl;
                    continue;
                }
            }
            else {
                if (y > board.getHeight() / 2) {
                    std::cout << "A tropa do Sul deve ser posicionada no lado inferior" << std::endl;
                    continue;
                }
            }
            Troop * t;
            Troop::TroopType ttype;
            if (type == 1) t = new AxialTroop(player, x, y);
            else if (type == 2) t = new DiagonalTroop(player, x, y);
            else if (type == 3 && specialPlaced <= specialTroopsPerPlayer) {
                if (player == Troop::Player::North) t = new SpecialWallTroop(player, x, y);
                else t = new SpecialBombTroop(player, x, y);   
            }
            else {
                std::cout << "Tipo invalido" << std::endl;
                continue;
            }

            board.getTile({x,y}).setOccupant(t);
            if (type == 3) specialPlaced++;
            placed++;
        }
    }
}

void Game::battleLoop() {
    std::cout << "A batalha se inicia!\n";
    while (board.countTroopsOwner(Troop::Player::North) > 0 && board.countTroopsOwner(Troop::Player::South) > 0) {
        board.displayBoard();
        std::cout << "Vez do jogador do " << Troop::typeToString(currentPlayer) << std::endl;
        std::cout << "Selecione o guerreiro (x y): ";
    
        int sx, sy;
        if (!(std::cin >> sx >> sy)) { std::cin.clear(); std::cin.ignore(10000,'\n'); continue; }
        if (!inBoard(sx, sy)) { std::cout << "Fora dos limites do tabuleiro\n"; continue; }
        Troop * t = board.getTroop({sx, sy});
        if (!t) { std::cout << "Nao existe guerreiro nessa posicao\n"; continue; }
        if (currentPlayer != t->getOwner()) { std::cout << "Esse guerreiro pertence ao oponente\n"; continue; }


        std::cout << "Escolha a acao: (1: mover, 2: atacar) ";
        int action;
        if (!(std::cin >> action)) { std::cin.clear(); std::cin.ignore(10000,'\n'); continue; }

        if (action == 1) doMove(t);
        else if (action == 2) doAttack(t);
        else { std::cout << "Acao invalida\n"; continue; }

        currentPlayer = (currentPlayer == Troop::Player::North ? Troop::Player::South : Troop::Player::North);
    }

    if (board.countTroopsOwner(Troop::Player::North) == 0) std::cout << "Sul vence!" << std::endl;
    else std::cout << "Norte vence!" << std::endl;

    askRestart();
}

void Game::doMove(Troop * t) {
    Position p = t->getPos();
    std::vector<Position> moves;

    const int dxs[4] = {1,-1,0,0}, dys[4] = {0,0,1,-1};
    for (int i = 0; i < 4; ++i) {
        int nx = p.x + dxs[i], ny = p.y + dys[i];
        if (!inBoard(nx,ny)) continue;
        if (board.getTile({nx,ny}).getOccupant() == nullptr && board.isWalkable({nx,ny})) moves.push_back({nx,ny});
    }

    if (moves.empty()) { std::cout << "Nenhum movimento possivel" << std::endl; return; }

    std::cout << "Movimentos possiveis:" << std::endl;
    for (Position &m : moves) std::cout << "("<<m.x<<", "<<m.y<<") " << std::endl;
    std::cout << "Escolha o (x y) desejado: ";
    int tx, ty; if (!(std::cin >> tx >> ty)) { std::cin.clear(); std::cin.ignore(10000,'\n'); return; }

    auto it = std::find_if(moves.begin(), moves.end(), [&](const Position& q){ return q.x==tx && q.y==ty; });
    if (it == moves.end()) { std::cout << "Movimento invalido\n"; return; }

    board.getTile({p.x,p.y}).setOccupant(nullptr);
    t->moveTo(tx,ty);
    board.getTile({tx,ty}).setOccupant(t);
    std::cout << "Movido para ("<<tx<<", "<<ty<<")" << std::endl;
}

void Game::doAttack(Troop * t) {
    if (t->getType() == Troop::TroopType::Axial) t->attack(board, {-1,-1});
    if (t->getType() == Troop::TroopType::Diagonal){
        std::cout << "Atacar para:\nDiagonal esquerda (1)\nDiagonal direita (2)" << std::endl;
        int d;
        std::cin >> d;
        t->attack(board, {-1, -1}, d);
    }
    else if (t->getType() == Troop::TroopType::SpecialWall){
        std::cout << "Atacar para:\nDiagonal esquerda (1)\n" <<
        (t->getOwner() == Troop::Player::North ? "Baixo" : "Cima")
        << "(2)\nDiagonal direita (3)?" << std::endl;
        int d;
        std::cin >> d;
        t->attack(board, {-1, -1}, d-2);
    }
    else if (t->getType() == Troop::TroopType::SpecialBomb){
        std::cout << "Escolha a posicao do ataque (x y) ";
        Position p;
        std::cin >> p.x >> p.y;
        t->attack(board, p);
    }}

void Game::askRestart() {
    std::cout << "Jogar novamente? (s/n): ";
    char c; std::cin >> c;
    if (c == 's' || c == 'S') {
        cleanup();
        start();
    } else {
        std::cout << "Saindo.\n";
        cleanup();
    }
}
