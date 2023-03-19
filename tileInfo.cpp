#include "tileInfo.h"

std::map<int, std::vector<Road>> TileInfo::roadInTileMap = {
    {
        1,
        {
            Road({
                Node(std::pair<float, float>(0.0, 0.5)),
                Node(std::pair<float, float>(1.0, 0.5))
            })
        }
    }
};

std::map<int, std::vector<RoadInfo>> TileInfo::roadInterConnection = {
    {
        1, 
        {
            RoadInfo(
                true, true,
                1, 1,
                3, 1
            )
        }
    }
};