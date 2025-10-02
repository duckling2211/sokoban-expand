#pragma once
#include "GameObject.h"

class Goal : public GameObject {
public:
    char getSymbol() const override { return '.'; }
    bool isWalkable() const override { return true; }
    void interact(GameObject*) override {}
};
