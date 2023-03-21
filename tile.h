#ifndef H_TILE
#define H_TILE

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "tileInfo.h"
#include "tilemap.h"

class Tilemap;

class Node {
    public:
        std::pair<float, float> relativePos;
        int posX;
        int posY;

        Node(std::pair<float, float> rel);
        void setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight);
};

class Road {
    public:
        std::vector<Node> nodes;
        std::vector<Road*> inputRoads;
        std::vector<Road*> outputRoads;

        void addInputRoad(Road* road);
        void addOutputRoad(Road* road);

        void setAllPosOfNodeFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight);

        Road(std::vector<Node> nodes);
};

class Tile {
    public:
        int posX;
        int posY;
        int width;
        int height;
        int rowIdx;
        int colIdx;

        int tileId;
        std::vector<Road> roads;

        Tilemap* parentTilemap;

        sf::RenderWindow* myWindow;

        Tile(int posX, int posY, int width, int height, int tileId, Tilemap* parentTile, int rowIdx, int colIdx);
        void Debug(int &c);
        void SetUpRoadConnection(); 

        Road* GetRoad(int side, int idx, bool isInputRoad);
};

#endif