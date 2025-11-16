#include "Board.hpp"
#include "Troop.hpp"
#include <vector>

class Game {
private:
    Board board;
    std::vector<Troop*> p1Troops;
    std::vector<Troop*> p2Troops;

    int currentPlayer = 1;
    int specialUsesP1 = 4;
    int specialUsesP2 = 4;

public:
    void start();
    void placementPhase();
    void gameLoop();
};