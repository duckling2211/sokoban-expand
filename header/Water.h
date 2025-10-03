#pragma once
#include "GameObject.h"

class Water : public GameObject {
public:
    char getSymbol() const override { return '-'; }
    bool isWalkable() const override { return true; }
    void interact(GameObject*) override {}
};

class LeftWater : public Water {
public:
    char getSymbol() const override { return '<'; }
    bool isWalkable() const override { return true; }
};

class RightWater : public Water {
public:
    char getSymbol() const override { return '>'; }
    bool isWalkable() const override { return true; }
};
