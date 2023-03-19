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

struct RoadInfo {
    public:
        bool inputFromOtherTile; 
        bool outputToOtherTile;
        int inputId;
        int outputId;
        int extraSideIn;
        int extraSideOut;

        RoadInfo(bool inputFromRoad, bool outputToRoad, 
            bool inputId, bool outputId, 
            int extraSideIn, int extraSideOut) 
        {
            this->inputFromOtherTile = inputFromRoad;
            this->outputToOtherTile = outputToRoad;

            this->inputId = inputId;
            this->outputId = outputId;

            this->extraSideIn = extraSideIn;
            this->extraSideOut = extraSideOut;
        }

        /*
        Explaination:
        If the road takes input from road from OTHER TILE, the inputId refers to the input number of the TILE,  (1)
        else, the inputId refers to the id number of the other ROAD (that lead to this road)    (2)

        Same with outputId.

        The `extraSideIn`, `extraSideOut` refers to the side which the inputId take from, 
            0 for up,
            1 for right,
            2 for down,
            3 for left
        in case (1).

        In case (2) `extraSideIn` can be safely set to -1. 
        Same with `extraSideOut`
        */
};

class TileInfo {
    public:
        static std::map<int, std::vector<Road>> roadInTileMap;
        static std::map<int, std::vector<RoadInfo>> roadInterConnection;
};

#endif