#pragma once
#include "GameObject.h"
class Delicate : public GameObject {
public:
    char getSymbol() const override { return 'F'; }
    bool isWalkable() const override { return true; }
    void interact(GameObject*) override {}
};
