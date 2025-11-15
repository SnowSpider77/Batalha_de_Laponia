#ifndef TILE_H
#define TILE_H

class Tile {
public:
    enum class Type { FLOOR, WALL, RIVER };

private:
    int x, y;
    Type type;
    char state;

public:
    Tile(int x, int y, char state = '.');

    int getType() const;
    void setType(Type newType);

    char getState() const;
    void setState(char newState);

    int getX() const;
    int getY() const;
};

#endif