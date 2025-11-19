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

    Troop::Player currentPlayer;
    int specialUsesNorth;
    int specialUsesSouth;
    int troopsPerPlayer;
    int specialTroopsPerPlayer;

    // phases
    void placementPhase();
    void battleLoop();

    // actions
    void doMove(Troop * t);
    void doAttack(Troop * t);

    // helpers
    bool inBoard(int x, int y) const;
    void cleanup();
    void askRestart();
};
