#include "Map.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Crate.h"
#include "GoalTile.h"
#include "FloorTile.h"
#include "Player.h"

Map::~Map() {
    for (auto& row : grid) {
        for (auto& tile : row) {
            delete tile.object;
            delete tile.ground;
        }
    }
    // delete player; // removed, already deleted in grid
}

void Map::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        std::vector<Tile> row;
        for (size_t x = 0; x < line.size(); ++x) {
            char c = line[x];
            Tile tile;
            tile.ground = new Floor();
            switch (c) {
                case '#': tile.object = new Wall(); break;
                case '*': tile.object = new Crate(); break;
                case '.': delete tile.ground; tile.ground = new Goal(); break;
                case '+': tile.object = new Crate(); delete tile.ground; tile.ground = new Goal(); break;
                case '@':
                    player = new Player();
                    playerX = x;
                    playerY = grid.size();
                    tile.object = player;
                    break;
            }
            row.push_back(tile);
        }
        grid.push_back(row);
    }
}

void Map::render() {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            Tile& tile = grid[y][x];
            if (tile.object && tile.ground && dynamic_cast<Goal*>(tile.ground) && dynamic_cast<Crate*>(tile.object))
                std::cout << '+';
            else if (tile.object)
                std::cout << tile.object->getSymbol();
            else if (tile.ground)
                std::cout << tile.ground->getSymbol();
            else
                std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void Map::movePlayer(char input) {
    int dx = 0, dy = 0;
    switch (tolower(input)) {
        case 'w': dy = -1; break;
        case 's': dy = +1; break;
        case 'a': dx = -1; break;
        case 'd': dx = +1; break;
        default: return;
    }

    int nx = playerX + dx;
    int ny = playerY + dy;
    int nx2 = playerX + 2 * dx;
    int ny2 = playerY + 2 * dy;

    if (ny < 0 || ny >= (int)grid.size() || nx < 0 || nx >= (int)grid[0].size()) return;
    Tile& next = grid[ny][nx];

    if (!next.object) {
        grid[playerY][playerX].object = nullptr;
        next.object = player;
        playerX = nx;
        playerY = ny;
    }
    else if (Crate* crate = dynamic_cast<Crate*>(next.object)) {
        if (ny2 < 0 || ny2 >= (int)grid.size() || nx2 < 0 || nx2 >= (int)grid[0].size()) return;
        Tile& beyond = grid[ny2][nx2];
        if (!beyond.object) {
            beyond.object = crate;
            next.object = player;
            grid[playerY][playerX].object = nullptr;
            playerX = nx;
            playerY = ny;
        }
    }
}

bool Map::isVictory() {
    for (auto& row : grid) {
        for (auto& tile : row) {
            if (dynamic_cast<Goal*>(tile.ground)) {
                if (!dynamic_cast<Crate*>(tile.object))
                    return false;
            }
        }
    }
    return true;
}
