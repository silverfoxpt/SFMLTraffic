#ifndef H_NODES
#define H_NODES

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class SaveNode {
    public:
        sf::Vector2f relativePos;
        sf::Vector2f mapPos;

        SaveNode() {}
};

class SaveRoad {
    public:
        std::vector<SaveNode> nodes;

        SaveRoad() {}
};

class SaveIntersectingNode {
    public:
        SaveNode posNode;
        std::vector<int> intersectingRoadIndex;
        std::vector<int> startNodeIdx;
};

class SaveIntraConnection {
    public:
        int inputRoadIdx;
        int outputRoadIdx;

        bool isEqual(SaveIntraConnection& other) {return (this->inputRoadIdx == other.inputRoadIdx) && (this->outputRoadIdx == other.outputRoadIdx); }
};

class SaveInterConnection {
    public:
        int roadIdx;
        int portIdx; //counted left to right and top to bottom
        int sideIdx; // 0 top, 1 right, 2 down, 3 left
        int inputOrOutput; // 0 for input, 1 for output

        bool isEqual(SaveInterConnection& other) {return (this->roadIdx == other.roadIdx) && (this->inputOrOutput == other.inputOrOutput); }
};

#endif