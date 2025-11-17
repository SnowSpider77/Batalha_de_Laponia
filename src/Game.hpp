#pragma once

#include <vector>
#include "Board.hpp"
#include "Troop.hpp"

class Game {
public:
    Game(int width = 12, int height = 12, int troopsPerPlayer = 8);

    void start();

private:
    Board board;
    std::vector<Troop*> northTroops;
    std::vector<Troop*> southTroops;

    int currentPlayer;
    int specialUsesNorth;
    int specialUsesSouth;
    int troopsPerPlayer;

    // phases
    void placementPhase();
    void battleLoop();

    // actions
    void doMove(Troop * t);
    void doAttack(Troop * t);

    // helpers
    bool inBoard(int x, int y) const;
    void cleanup();
    int countTroops(int player) const;
    void askRestart();
};
