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

class Node {
    public:
        std::pair<float, float> relativePos;
        int posX;
        int posY;
};

class Tile {
    public:
        int posX;
        int posY;
        float width;
        float height;

        int tileId;
        std::vector<Node> nodes;

        sf::RenderWindow* myWindow;

        Tile(int posX, int posY, int width, int height, int tileId);
        void Debug();
};

#endif