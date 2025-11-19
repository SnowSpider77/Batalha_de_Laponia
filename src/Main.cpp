#include <iostream>
#include "Game.hpp"

class MainClass {
public:
    void run() {
        int x, y, t, e;
        std::cout << "Escolha o tamanho do tabuleiro, quantidade de tropas total e de tropas especiais (x y c e): " << std::endl;
        std::cin >> x >> y >> t >> e;
        Game game(x, y, t, e);
        game.start();
    }
};

int main() {
    MainClass app;
    app.run();
    return 0;
}