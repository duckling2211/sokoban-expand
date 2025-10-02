#pragma once
#include <string>

class BaseMap {
public:
    virtual ~BaseMap() {}
    virtual void loadFromFile(const std::string& filename) = 0;
    virtual void render() = 0;
    virtual void movePlayer(char input) = 0;
    virtual bool isVictory() = 0;
    virtual bool hasFailed() const = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};
