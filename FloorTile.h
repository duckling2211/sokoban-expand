#pragma once
#include "GameObject.h"

class Floor : public GameObject {
public:
    char getSymbol() const override { return ' '; }
    bool isWalkable() const override { return true; }
    void interact(GameObject*) override {}
};
