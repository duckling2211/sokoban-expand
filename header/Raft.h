#pragma once
#include "GameObject.h"

class Raft : public GameObject {
public:
    char getSymbol() const override { return 'R'; }
    bool isWalkable() const override { return false; }
    void interact(GameObject*) override {}
};
