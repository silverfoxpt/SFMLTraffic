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

class Node {
    public:
        std::pair<float, float> relativePos;
        int posX;
        int posY;

        Node(std::pair<float, float> rel);
        void setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight);
};

class Tile {
    public:
        int posX;
        int posY;
        int width;
        int height;

        int tileId;
        std::vector<Node> nodes;
        std::map<int, std::vector<int>> neighbor;

        sf::RenderWindow* myWindow;

        Tile(int posX, int posY, int width, int height, int tileId);
        void Debug();
};

#endif