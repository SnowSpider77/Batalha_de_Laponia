#ifndef TROOP_H
#define TROOP_H

struct Position{
    int x;
    int y;
};

class Troop {
private:
    Position pos;

public:
    enum class AttackDirection { AXIAL, DIAGONAL };

    Troop(int x, int y);

    virtual ~Troop() = default; // Virtual destructor for polymorphism
    virtual void attack() = 0;  // Pure virtual function to make the class abstract

    Position getPos() const;
    void moveTo(int x, int y);
    void moveDelta(int dx, int dy);
};

#endif