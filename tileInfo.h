#ifndef H_TILEINFO
#define H_TILEINFO

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "tile.h"

class TileInfo {
    public:
        static std::map<int, std::vector<std::pair<float, float>>> nodePosMapper;
        static std::map<int, std::vector<std::pair<int, int>>> nodeConnectionMapper;
        static std::map<int, std::vector<std::vector<int>>> nodeNeighborMap;
};

#endif