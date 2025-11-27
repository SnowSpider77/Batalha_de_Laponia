#pragma once

#include <vector>
#include "Board.hpp"
#include "Troop.hpp"

class Game {
public:
    Game(int width = 10, int height = 10, int troopsPerPlayer = 8, int specialTroopsPerPlayer = 1);

    void start();

    Board& getBoard();

private:
    Board board;

    Troop::Player currentPlayer; // Controla qual o jogador da vez
    int specialUsesNorth; // Número de usos da habilidade especial restante
    int specialUsesSouth;
    int troopsPerPlayer; // Tropas normais por jogador
    int specialTroopsPerPlayer; // Tropas especiais por jogador

    // Fases principais
    void placementPhase();
    void battleLoop();

    // Ações das tropas
    void doMove(Troop * t);
    void doAttack(Troop * t);

    // Funções auxiliares
    bool inBoard(int x, int y) const;
    void cleanup();
    void askRestart();
};
