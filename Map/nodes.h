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

#endif