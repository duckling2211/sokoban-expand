#pragma once
#include "BaseMap.h"
#include <vector>
#include <deque>
#include "Tile.h"
#include "Player.h"
class GardenMap : public BaseMap {
private:
    std::vector<std::vector<Tile>> grid;
    std::deque<std::vector<std::vector<Tile>>> undoStack;
    std::deque<std::vector<std::vector<Tile>>> redoStack;
    const size_t maxHistory = 20;
    Player* player = nullptr;
    int playerX = 0, playerY = 0;
    bool failed = false;
public:
    ~GardenMap();
    void loadFromFile(const std::string& filename) override;
    void render() override;
    void movePlayer(char input) override;
    bool isVictory() override;
    bool hasFailed() const override { return failed; }
    void undo() override;
    void redo() override;
};
