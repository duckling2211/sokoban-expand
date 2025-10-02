#pragma once
class Player;

class GameObject {
public:
    virtual char getSymbol() const = 0;
    virtual bool isWalkable() const = 0;
    virtual void interact(GameObject*) = 0;
    virtual ~GameObject() {}
};
