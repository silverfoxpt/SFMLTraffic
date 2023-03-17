#include "tileInfo.h"

std::map<int, std::vector<std::pair<float, float>>> TileInfo::nodePosMapper = {
    {
        1,
        {
            std::pair<float, float>(0.0, 0.5),  //middle left
            std::pair<float, float>(1.0, 0.5)   //middle right
        }
    }
};

std::map<int, std::vector<std::pair<int, int>>> TileInfo::nodeConnectionMapper = {
    {
        1,
        {
            std::pair<int, int>(0, 1)
        }
    }
};

std::map<int, std::vector<std::vector<int>>> TileInfo::nodeNeighborMap = {
    1, 
    {
        {},
        {1},
        
    }
};