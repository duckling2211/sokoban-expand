#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
    char getSymbol() const override { return '#'; }
    bool isWalkable() const override { return false; }
    void interact(GameObject*) override {}
};
