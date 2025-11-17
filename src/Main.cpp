#include <iostream>
#include "Game.hpp"

class MainClass {
public:
    void run() {
        Game game = Game(5, 5, 2);
        game.start();
    }
};

int main() {
    MainClass app;
    app.run();
    return 0;
}