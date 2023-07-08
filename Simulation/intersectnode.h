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

class TileIntersectManager {
    public:
        std::vector<IntersectNode> nodes;
};

class IntersectManager {
    public:
        std::vector<std::vector<TileIntersectManager>> managers;

        IntersectManager() {} //default

        void addNode(IntersectNode inter, int row, int col) {
            if (managers.size() == 0 || row < 0 || col < 0 || row >= (int) managers.size() || col >= (int) managers[0].size()) {
                std::cout << "Error: Manager not exist";
                return;
            }
            this->managers[row][col].nodes.push_back(inter);
        }

        IntersectNode* getIntersectNode(int row, int col, int id) {
            if (managers.size() == 0 || row < 0 || col < 0 || row >= (int) managers.size() || col >= (int) managers[0].size()) {
                std::cout << "Error: Manager not exist";
                return nullptr;
            }
            auto &manager = this->managers[row][col];
            if (id < 0 || id >= (int) manager.nodes.size()) {
                std::cout << "Error: Intersect idx not found";
                return nullptr;
            }
            return &manager.nodes[id];
        }

        void HardReset() {
            managers.clear();
        }

        void Initialize(int rows, int cols) {
            for (int i = 0; i < rows; i++) {
                std::vector<TileIntersectManager> tileman; this->managers.push_back(tileman);
                for (int j = 0; j < cols; j++) {
                    TileIntersectManager interMan;
                    this->managers[i].push_back(interMan);
                }
            }    
        }


        //this must be called after Initialize()
        void InitializeNodes() {
            for (auto &row: this->managers) {
                for (auto& manager: row) {
                    for (auto& node: manager.nodes) {
                        node.InitializeIntersectNode();
                    }
                }
            }
        }

        void Visualize(sf::RenderWindow* rend) {
            //draw position of intersections
            for (auto &row: this->managers) {
                for (auto& manager: row) {
                    for (auto& node: manager.nodes) {
                        DrawUtils::drawCircle(rend, sf::Vector2f(node.posX, node.posY), 5, sf::Color::Red); 
                        //std::cout << node.posX << " " << node.posY << '\n';
                    }
                }
            }
        }

        void Update() {
           for (auto &row: this->managers) {
                for (auto& manager: row) {
                    for (auto& node: manager.nodes) {
                        node.Update();
                    }
                }
            }
        }

};

#endif