#pragma once
#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"

class Map {
private:
    std::vector<std::vector<Tile>> grid;
    Player* player = nullptr;
    int playerX = 0, playerY = 0;
public:
    ~Map();
    void loadFromFile(const std::string& filename);
    void render();
    void movePlayer(char input);
    bool isVictory();
};
