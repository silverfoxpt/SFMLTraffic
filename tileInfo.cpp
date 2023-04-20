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
    },
    {
        2, 
        {
            Road({
                Node(std::pair<float, float>(0.0, 0.7)),
                Node(std::pair<float, float>(0.3, 0.7)),
                Node(std::pair<float, float>(0.4, 0.67)),
                Node(std::pair<float, float>(0.47, 0.6)),

                Node(std::pair<float, float>(0.5, 0.5)),

                Node(std::pair<float, float>(0.53, 0.4)),
                Node(std::pair<float, float>(0.6, 0.33)),
                Node(std::pair<float, float>(0.7, 0.3)),
                Node(std::pair<float, float>(1.0, 0.3)),
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
    },
    {
        //error here, needed to be longer
        2, 
        {
            RoadInfo(
                true, true,
                1, 1,
                3, 1
            )
        }
        
    }
};