#ifndef H_INTERSECTNODE
#define H_INTERSECTNODE

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

class IntersectNode {
    public:
        int posX, posY;
        float displace1, displace2;
        std::vector<Road*> myRoads;

        IntersectNode(sf::Vector2i pos, float displace1, float displace2) {
            this->posX = pos.x;
            this->posY = pos.y;

            this->displace1 = displace1;
            this->displace2 = displace2;
        }

        void addRoad(Road* newRoad) {
            myRoads.push_back(newRoad);
        }
};

class IntersectManager {
    public:
        static std::vector<IntersectNode> intersections;

        static void Update() {

        }

        static void addNode(IntersectNode inter) {
            intersections.push_back(inter);
        }
};

#endif