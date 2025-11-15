#include "warrior.hpp"
#include "Troop.hpp"

#include <string>
#include <iostream>
#include <algorithm>

class Warrior : public Troop {
public:

    Warrior (int x, int y, AttackDirection type = AttackDirection::DIAGONAL) : Troop(x, y), type_(type) {}

    Position position() const noexcept { return getPos(); }
    AttackDirection type() const noexcept { return type_; }   

private:
    AttackDirection type_;
};


// ...existing code...