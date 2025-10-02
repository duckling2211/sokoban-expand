#pragma once
#include "GameObject.h"

class Breakable : public GameObject {
public:
    char getSymbol() const override { return 'B'; }
    bool isWalkable() const override { return false; }
    void interact(GameObject*) override {}
};
