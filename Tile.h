#pragma once
#include "GameObject.h"

struct Tile {
    GameObject* ground = nullptr;   // e.g. Floor or Goal
    GameObject* object = nullptr;   // e.g. Player, Crate
};
