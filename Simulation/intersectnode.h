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
#include "gameManager.h"
#include "randomsfml.h"
#include "carInfo.h"

class Node;
class Road;
class Tile;
class Car;

class IntersectNode {
    public:
        int posX, posY;
        sf::Vector2f relativePos;

        std::vector<Road*> myRoads;
        std::vector<int> roadIdx; //only used temporarily
        std::vector<int> startNodeIdx;

        //displacements are also use to calculate traffic lights stoppage. Don't mess with this
        std::vector<int> displacements; //length from start of each road to the intersect node
        std::string UIUD;

        //TODO: UPDATE THIS SOMEWHERE!
        Tile* residentTile;

        Car* currentAcceptedCar = nullptr;
        int currentlyAcceptedRoad = -1;

        //for traffic node
        bool detecting = true;

        IntersectNode(sf::Vector2i pos) {
            this->posX = pos.x;
            this->posY = pos.y;

            this->UIUD = Randomize::rand.get_uuid();
        }

        IntersectNode(sf::Vector2f relativePos) {
            this->relativePos = relativePos;
        }

        void addRoad(Road* newRoad) {
            myRoads.push_back(newRoad);
        }

        void Update();
        void InitializeIntersectNode();
};

class IntersectManager {
    public:
        std::vector<IntersectNode> intersections;

        IntersectManager() {} //default

        void addNode(IntersectNode inter) {
            //std::cout << "Hello?\n";
            this->intersections.push_back(inter);
        }

        IntersectNode* getIntersectNode(int id) {
            if (id < 0 || id >= (int) this->intersections.size()) {
                std::cerr << "idx not found";
            }
            return &this->intersections[id];
        }

        void HardReset() {
            intersections.clear();
        }

        void Initialize() {
            for (auto &inter: intersections) {
                inter.InitializeIntersectNode();
            }
        }

        void Visualize(sf::RenderWindow* rend) {
            //draw position of intersections
            for (auto &inter: intersections) {
                DrawUtils::drawCircle(rend, sf::Vector2f(inter.posX, inter.posY), 5, sf::Color::Red); 
            }
        }

        void Update() {
            for (auto &inter: intersections) {
                inter.Update();
            }
        }

};

#endif