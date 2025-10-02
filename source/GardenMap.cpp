#include "GardenMap.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Wall.h"
#include "Crate.h"
#include "GoalTile.h"
#include "FloorTile.h"
#include "Player.h"
//#include "Delicate.h" // Commented out
//#include "Breakable.h" // Commented out

GardenMap::~GardenMap() {
    for (auto& row : grid) {
        for (auto& tile : row) {
            delete tile.object;
            delete tile.ground;
        }
    }
    player = nullptr;
}

void GardenMap::loadFromFile(const std::string& filename) {
    for (auto& row : grid) {
        for (auto& tile : row) {
            delete tile.object;
            delete tile.ground;
        }
    }
    grid.clear();
    undoStack.clear();
    redoStack.clear();
    player = nullptr;
    failed = false;

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
                // case 'F': tile.object = new Delicate(); break; // Commented out
                // case 'B': tile.object = new Breakable(); break; // Commented out
            }
            row.push_back(tile);
        }
        grid.push_back(row);
    }
}

void GardenMap::render() {
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
    if (failed) {
        std::cout << "\nA crate destroyed a delicate tile. Mission failed.\n"; // Optional: remove message entirely if no delicate tiles
    }
}

void GardenMap::movePlayer(char input) {
    if (failed) return;

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

    // Remove delicate check, just simple movement:
    if (!next.object /*|| dynamic_cast<Delicate*>(next.object)*/) {
        // if (dynamic_cast<Breakable*>(next.object)) return; // Commented out
        if (undoStack.size() >= maxHistory) undoStack.pop_front();
        undoStack.push_back(grid);
        redoStack.clear();
        grid[playerY][playerX].object = nullptr;
        next.object = player;
        playerX = nx;
        playerY = ny;
    }
    else if (Crate* crate = dynamic_cast<Crate*>(next.object)) {
        if (ny2 < 0 || ny2 >= (int)grid.size() || nx2 < 0 || nx2 >= (int)grid[0].size()) return;
        Tile& beyond = grid[ny2][nx2];
        // Remove delicate/breakable behavior:
        /*
        if (Delicate* d = dynamic_cast<Delicate*>(beyond.object)) {
            delete beyond.object;
            beyond.object = nullptr;
            delete crate;
            next.object = nullptr;
            failed = true;
            return;
        }
        if (Breakable* b = dynamic_cast<Breakable*>(beyond.object)) {
            delete beyond.object;
            beyond.object = nullptr;
            delete crate;
            next.object = nullptr;
        }
        */
        if (!beyond.object || dynamic_cast<Goal*>(beyond.object)) {
            if (undoStack.size() >= maxHistory) undoStack.pop_front();
            undoStack.push_back(grid);
            redoStack.clear();
            beyond.object = crate;
            next.object = player;
            grid[playerY][playerX].object = nullptr;
            playerX = nx;
            playerY = ny;
        }
    }
}

void GardenMap::undo() {
    if (!undoStack.empty()) {
        if (redoStack.size() >= maxHistory) redoStack.pop_front();
        redoStack.push_back(grid);
        grid = undoStack.back();
        undoStack.pop_back();
        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x].object == player) {
                    playerX = x;
                    playerY = y;
                    return;
                }
            }
        }
    }
}

void GardenMap::redo() {
    if (!redoStack.empty()) {
        if (undoStack.size() >= maxHistory) undoStack.pop_front();
        undoStack.push_back(grid);
        grid = redoStack.back();
        redoStack.pop_back();
        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x].object == player) {
                    playerX = x;
                    playerY = y;
                    return;
                }
            }
        }
    }
}

bool GardenMap::isVictory() {
    if (failed) return false;
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
