#include "tileInfo.h"

std::map<int, std::vector<Road>> TileInfo::roadInTileMap = {
    {
        0,
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
    },
    {
        3, 
        {
            Road({
                Node(std::pair<float, float>(0.0, 0.3)),
                Node(std::pair<float, float>(0.5, 0.5)),
            }),
            Road({
                Node(std::pair<float, float>(0.0, 0.7)),
                Node(std::pair<float, float>(0.5, 0.5)),
            }),
            Road({
                Node(std::pair<float, float>(0.5, 0.5)),
                Node(std::pair<float, float>(1.0, 0.5)),
            })
        }
    },
    {
        4,
        {
            Road({
                Node(std::pair<float, float>(0.0, 0.5)),
                Node(std::pair<float, float>(0.5, 0.3)),
            }),
            Road({
                Node(std::pair<float, float>(0.0, 0.5)),
                Node(std::pair<float, float>(0.5, 0.5)),
            }),
            Road({
                Node(std::pair<float, float>(0.0, 0.5)),
                Node(std::pair<float, float>(0.5, 0.7)),
            }),
            Road({
                Node(std::pair<float, float>(0.5, 0.3)),
                Node(std::pair<float, float>(1.0, 0.5)),
            }),
            Road({
                Node(std::pair<float, float>(0.5, 0.5)),
                Node(std::pair<float, float>(1.0, 0.5)),
            }),
            Road({
                Node(std::pair<float, float>(0.5, 0.7)),
                Node(std::pair<float, float>(1.0, 0.5)),
            }),
        }
    }
};

//reclassified
std::map<int, std::vector<RoadInterInfo>> TileInfo::roadInterConnection = {
    {
        0, 
        {
            RoadInterInfo(
                true, true,
                5, 5, //input at 0.5, output at 0.5 -> 5, 5
                3, 1,
                0
            )
        }
    },
    {
        //error here, needed to be longer
        2, 
        {
            RoadInterInfo(
                true, true,
                1, 1,
                3, 1, 
                0
            )
        }
        
    },
    {
        3, 
        {
            RoadInterInfo(
                true, false,
                3, -1,
                3, -1, 
                0
            ),
            RoadInterInfo(
                true, false,
                7, -1,
                3, -1,
                1
            ),
            RoadInterInfo(
                false, true,
                -1, 5,
                -1, 1, 
                2
            )
        }   
    },
    {
        4,
        {
            RoadInterInfo(
                true, false,
                5, -1,
                3, -1,
                0
            ),
            RoadInterInfo(
                true, false,
                5, -1,
                3, -1, 
                1
            ),
            RoadInterInfo(
                true, false,
                5, -1,
                3, -1, 
                2
            ),
            RoadInterInfo(
                false, true,
                -1, 5,
                -1, 1,
                3
            ),
            RoadInterInfo(
                false, true,
                -1, 5,
                -1, 1, 
                4
            ),
            RoadInterInfo(
                false, true,
                -1, 5,
                -1, 1, 
                5
            )
        }
    }
};

//newly classified
std::map<int, std::vector<std::pair<int, int>>> TileInfo::roadIntraConnection = {
    {
        0,
        {

        }
    },
    {
        2,
        {
            std::pair<int, int>(0, 1),
            std::pair<int, int>(1, 2),
            std::pair<int, int>(2, 3),
            std::pair<int, int>(3, 4),
            std::pair<int, int>(4, 5),
            std::pair<int, int>(5, 6),
            std::pair<int, int>(6, 7),
            std::pair<int, int>(7, 8)
        }
    },
    {
        3,
        {
            std::pair<int, int>(0, 2),
            std::pair<int, int>(1, 2)
        }
    },
    {
        4,
        {
            std::pair<int, int>(0, 3),
            std::pair<int, int>(1, 4),
            std::pair<int, int>(2, 5),
        }
    }
};

int TileInfo::largestId() {
    int maxi = 0;
    for (auto it = roadInTileMap.begin(); it != roadInTileMap.end(); it++) {
        maxi = std::max(maxi, it->first+1);
    }
    return maxi;
}

void TileInfo::clearAll() {
    roadInterConnection.clear();
    roadInTileMap.clear();
    roadIntraConnection.clear();
}
