#pragma once
#include "GameObject.h"

class Crate : public GameObject {
public:
    char getSymbol() const override { return '*'; }
    bool isWalkable() const override { return false; }
    void interact(GameObject*) override {}
};
