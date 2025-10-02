#pragma once
#include "BaseMap.h"
#include <memory>
#include <string>
class MapFactory {
public:
    static std::unique_ptr<BaseMap> create(const std::string& type);
};
