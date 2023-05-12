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
#include "../drawshapes.h"

class Node;
class Road;
class Tile;

class IntersectNode {
    public:
        int posX, posY;
        sf::Vector2f relativePos;

        std::vector<Road*> myRoads;
        std::vector<int> roadIdx; //only used temporarily
        std::vector<int> startNodeIdx;

        //TODO: UPDATE THIS SOMEWHERE!
        Tile* residentTile;

        IntersectNode(sf::Vector2i pos) {
            this->posX = pos.x;
            this->posY = pos.y;
        }

        IntersectNode(sf::Vector2f relativePos) {
            this->relativePos = relativePos;
        }

        void addRoad(Road* newRoad) {
            myRoads.push_back(newRoad);
        }

        void PopulateIntersectNode();
};

class IntersectManager {
    public:
        std::vector<IntersectNode> intersections;

        IntersectManager() {} //default

        void addNode(IntersectNode inter) {
            this->intersections.push_back(inter);
        }

        void Initialize() {
            for (auto &inter: intersections) {
                inter.PopulateIntersectNode();
            }
        }

        void Visualize(sf::RenderWindow* rend) {
            //draw position of intersections
            for (auto& inter: intersections) {
                DrawUtils::drawCircle(rend, sf::Vector2f(inter.posX, inter.posY), 3.5, sf::Color::Red); 
            }
        }

};

#endif