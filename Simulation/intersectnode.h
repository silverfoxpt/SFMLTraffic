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

        void PopulateIntersectNode() {
            if (residentTile == nullptr) {std::cerr << "Need Tile!\n"; return;}

            //update position
            sf::Vector2f corner = this->residentTile->getCornerPos();
            int size = this->residentTile->parentTilemap->tileWidth;

            this->posX = corner.x + size * relativePos.x;
            this->posY = corner.y + size * relativePos.y;

            //update road
            for (int x: roadIdx) {
                Road* road = residentTile->getRoad(x);
                myRoads.push_back(road);
            }

            this->roadIdx.clear(); //release unneccessary space
        }
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