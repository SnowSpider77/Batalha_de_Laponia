#pragma once

#include<vector>
#include<stdexcept>

class Board;

// Struct para organizar posições, não é 100% necessário, mas deixa o código um pouco mais organizado
struct Position{
    int x;
    int y;
};

// Classe abstrata base para todas as tropas
class Troop {
public:
    // Enum para diferenciar os jogadores Norte e Sul
    enum class Player {North, South};
    // Enum para diferenciar os tipos de tropa
    // Apesar das diferentes classes já disporem dessa informação
    // Ter um enum ajuda a aumentar o desempenho e simplificar o código
    // Evitando ter que "descobrir" o tipo das tropas cada vez
    enum class TroopType { Axial, Diagonal, SpecialWall, SpecialBomb};

private:
    Position pos; // Posição
    Player owner; // Referencia qual o dono da tropa, essencial para o funcionamento final do jogo
    TroopType type; // Tipo da tropa
    char symbol; // Símbolo referente ao tipo da tropa

public:
    Troop(Player owner, int x, int y);
    virtual ~Troop() = default;

    Position getPos() const;
    void moveTo(int x, int y);

    Player getOwner() const;

    // Funções attack, existem duas sobrecargas (polimorfismo estático)
    // O motivo disso é que alguns ataques necessitam saber a direção d, que é uma informação extra
    virtual void attack(Board& board, Position p) {
        throw std::runtime_error("This troop requires more information for the attack");
    }
    virtual void attack(Board& board, Position p, int d) {
        throw std::runtime_error("This troop type does not support directional attack");
    }

    TroopType getType() const;
    static std::string typeToString(Player player);
    void setType(TroopType t);

    char getSymbol() const;
    void setSymbol(char c);
};

// Fuzileiro, atira só para frente
class AxialTroop : public Troop {
public:
    
    AxialTroop(Player owner, int x, int y);
    ~AxialTroop() = default;

    void attack(Board& board, Position p) override;
};

// Flanco, atira nas diagonais
class DiagonalTroop : public Troop {
public:
    DiagonalTroop(Player owner, int x, int y);
    ~DiagonalTroop() = default;

    void attack(Board& board, Position p, int d) override;
};

// Sniper, atira para frente, para as diagonais e o tiro atravessa as tropas sem parar
class SpecialWallTroop : public Troop {
public:
    SpecialWallTroop(Player owner, int x, int y);
    ~SpecialWallTroop() = default;

    void attack(Board& board, Position p, int d) override;
};

// Morteiro, atinge uma área 3x3 cujo centro é escolhido pelo jogador
class SpecialBombTroop : public Troop {
public:
    SpecialBombTroop(Player owner, int x, int y);
    ~SpecialBombTroop() = default;

    void attack(Board& board, Position p) override;
};