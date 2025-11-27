#pragma once

#include <vector>
#include "Tile.hpp"

class Board {
private:
    int width;
    int height;
    std::vector<std::vector<Tile>> board;

public:
    Board(int width, int height);

    void displayBoard() const;

    // Dois gets para permitir modificar o Tile diretamente
    Tile& getTile(Position p);
    Tile const& getTile(Position p) const;

    int getHeight() const;
    int getWidth() const;

    // Funções de controle dos limites do tabuleiro
    bool inBounds(Position P) const;
    bool isEmpty(Position p) const;
    bool isWalkable(Position p) const;

    // Funções de controle das tropas
    Troop * getTroop(Position p) const;
    void placeTroop(Position p, Troop * t);
    void removeTroop(Position p);
    void moveTroop(Position from, Position to);
    // Contagem das tropas de cada jogador, essencial para o fluxo do jogo
    int countTroopsOwner(Troop::Player owner);

    // Elimina todas as tropas do tabuleiro
    void clear();
};