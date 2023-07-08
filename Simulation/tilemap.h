#ifndef H_TILEMAP
#define H_TILEMAP

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

class Tile;
class IntersectManager;

class Tilemap {
    public:
        int xPos;
        int yPos;
        int rows;
        int cols;

        int tileWidth;
        int tileHeight;

        sf::RenderWindow* myWindow;

        std::vector<std::vector<Tile>> tilemap;
        std::vector<std::vector<int>> tileIds;
        
        Tilemap(int rows, int cols, int xPos, int yPos, int tileWidth, int tileHeight, sf::RenderWindow* myWindow, IntersectManager* interManager);
        Tilemap() {} //empty constructor
        void Debug();
        void Update();
        void ClearAndReset(IntersectManager* interManager);
        void SetUpAllTileIntersections();

        int* getTileID(int i, int j);

        bool TileExist(int row, int col);
        Tile* GetTile(int row, int col);
};

#endif