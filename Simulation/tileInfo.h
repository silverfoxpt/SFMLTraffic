#ifndef H_TILEINFO
#define H_TILEINFO

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

class Road;

struct RoadInterInfo {
    public:
        bool inputFromOtherTile; 
        bool outputToOtherTile;
        int inputId;
        int outputId;
        int extraSideIn;
        int extraSideOut;
        int roadId;

        RoadInterInfo(bool inputFromOtherTile, bool outputToOtherTile, 
            bool inputId, bool outputId, 
            int extraSideIn, int extraSideOut, int roadId) 
        {
            this->inputFromOtherTile = inputFromOtherTile;
            this->outputToOtherTile = outputToOtherTile;

            this->inputId = inputId;
            this->outputId = outputId;

            this->extraSideIn = extraSideIn;
            this->extraSideOut = extraSideOut;
            this->roadId = roadId;
        }

        /*
        Explaination:
        If the road takes input from road from OTHER TILE, the inputId refers to the input number of the TILE.
        Same with outputId.

        The `extraSideIn`, `extraSideOut` refers to the side which the inputId take from, 
            0 for up,
            1 for right,
            2 for down,
            3 for left
        in case (1).

        Else, inputId, outputId, extraSideIn, extraSideOut can be safely set to -1, cause it doesn't matter
        */
};

class TileInfo {
    public:
        static std::map<int, std::vector<Road>> roadInTileMap;
        static std::map<int, std::vector<RoadInterInfo>> roadInterConnection;
        static std::map<int, std::vector<std::pair<int, int>>> roadIntraConnection;

        static int largestId();
};

#endif