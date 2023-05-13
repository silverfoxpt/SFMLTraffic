#ifndef H_TILE
#define H_TILE

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "tileInfo.h"
#include "tilemap.h"
#include "car.h"
#include "gameManager.h"
#include "carInfo.h"
#include "randomsfml.h"

#include "intersectnode.h"

class Tilemap;
class IntersectNode;
class IntersectManager;

class Node {
    public:
        std::pair<float, float> relativePos;
        int posX;
        int posY;

        Node(std::pair<float, float> rel);
        Node(sf::Vector2i actualPos);
        void setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight);
        void Update();
        sf::Vector2f getPos();
};

class Road {
    public:
        int rowIdx, colIdx; //debug purpose
        float roadLength;

        bool outputBlocked = false;
        bool inputJammed = false;
        
        bool calculatedLengthNodeTo = false;

        std::vector<Node> nodes;
        std::vector<Road*> inputRoads;
        std::vector<Road*> outputRoads;

        std::vector<Car*> currentCars; //must be deleted when reused for other projects
        std::vector<int> carOnNode;
        std::vector<int> lengthNodeTo;

        sf::Vector2f getVectorBetweenTwoNodes(int startNodeIdx);
        float getLengthBetweenTwoNodes(int startNodeIdx);
        float getLengthFromStartToNode(int endNodeIdx);

        void addInputRoad(Road* road);
        void addOutputRoad(Road* road);
        void addNode(Node node);

        void setAllPosOfNodeFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight);
        void acceptCar(Car* newCar);
        void removeCar();
        void updateCars();

        void blockOutput();
        void CheckIfOutputBlocked();
        void CheckIfInputJammed();
        void UpdateCarVelocity();

        Road(std::vector<Node> nodes);
        Road() { } //default constructor

        void CalculateRoadLength();
        void Update();
};

class Tile {
    public:
        int posX;
        int posY;
        int width;
        int height;
        int rowIdx;
        int colIdx;

        int tileId;
        std::vector<Road> roads;

        Tilemap* parentTilemap;
        IntersectManager* intersectManager;

        sf::RenderWindow* myWindow;

        Tile(int posX, int posY, int width, int height, int tileId, Tilemap* parentTile, int rowIdx, int colIdx);
        void Debug(int &c);
        void Update();
        void SetUpRoadConnection(); 

        std::vector<Road*> GetInterRoad(int side, int idx, bool isInputRoad);

        Road* getRoad(int id);
        sf::Vector2f getCornerPos();
};

#endif