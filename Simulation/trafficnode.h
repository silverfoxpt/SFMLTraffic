#ifndef H_TRAFFICNODE
#define H_TRAFFICNODE

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

//forward declarations
class Tile;
class Tilemap;
class IntersectNode;
class IntersectManager;
class TileTrafficManager;

class TrafficNode {
    public:
        //need to be updated somewhere
        Tile* parentTile;
        IntersectNode* parentIntersectNode;
        TileTrafficManager* parentTrafficManager;

        std::vector<Road*> myRoad; //taken from intersect node
        std::vector<int> roadToPhase;

        void Initialize(Tile* parentTile, IntersectNode* parentIntersectNode, TileTrafficManager* parentTrafficManager);
};

class TileTrafficManager {
    public:
        std::vector<TrafficNode> nodes;
        std::vector<float> phaseTimes;
        int currentPhase = 0;
        float currentTimer = 0;

        //need to be updated somewhere
        Tile* parentTile;

        void Initialize(Tile* parentTile, IntersectManager* intersectManager, int tileId);
};

class TrafficManager {
    public:
        std::vector<std::vector<TileTrafficManager>> managers;

        void Initialize(Tilemap* tilemap, IntersectManager* intersectManager);
};

#endif