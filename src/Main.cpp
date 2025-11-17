#include <iostream>
#include "Game.hpp"

class MainClass {
public:
    void run() {
        Game game = Game();
        game.start();
    }
};

int main() {
    MainClass app;
    app.run();
    return 0;
}