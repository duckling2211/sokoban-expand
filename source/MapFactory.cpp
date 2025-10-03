#include "MapFactory.h"
#include "GardenMap.h"
#include "OceanMap.h"
// TODO: include OceanMap, LavaMap later
std::unique_ptr<BaseMap> MapFactory::create(const std::string& type) {
    if (type == "garden") return std::make_unique<GardenMap>();
    else if (type == "ocean") return std::make_unique<OceanMap>();
    // else if (type == "lava") return std::make_unique<LavaMap>();
    return nullptr;
}
