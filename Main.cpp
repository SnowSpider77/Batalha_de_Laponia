#include <iostream>
#include "Board.hpp"

class MainClass {
public:
    void run() {
        Board board = Board();
        board.displayBoard();
    }
};

int main() {
    MainClass app;
    app.run();
    return 0;
}