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
        std::shared_ptr<Road> inputRoad;
        std::shared_ptr<Road> outputRoad;

        void setInputRoad(std::shared_ptr<Road> road);
        void setOutputRoad(std::shared_ptr<Road> road);

        void setAllPosOfNodeFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight);

        Road(std::vector<Node> nodes);
};

class Tile {
    public:
        int posX;
        int posY;
        int width;
        int height;

        int tileId;
        std::vector<Road> roads;

        Tilemap* parentTilemap;

        sf::RenderWindow* myWindow;

        Tile(int posX, int posY, int width, int height, int tileId, Tilemap* parentTile);
        void Debug();
        void SetUpConnection();
};

#endif