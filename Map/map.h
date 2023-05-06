#ifndef H_MAP
#define H_MAP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "drawbezier.h"
#include "drawmap.h"
#include "intersectmap.h"
#include "intraconnect.h"

#include "nodes.h"

#include "../Simulation/gameManager.h"

class Drawmap;
class DrawBezier;
class IntersectMap;
class MapIntraConnect;

class Map {
    public:
        //initialize
        sf::RenderWindow* rend;
        int drawStatus          = 0;
        int size                = 400;
        sf::Vector2f offset     = sf::Vector2f(50, 50);
        int numGrid             = 20;

        //child class
        Drawmap* myDrawmap;
        DrawBezier* myDrawBezier;
        IntersectMap* myIntersectMap;
        MapIntraConnect* myIntraconnectMap;

        //important stuffs - must be updated if anything changes
        std::vector<SaveRoad> roads;
        std::vector<SaveIntersectingNode> intersections;
        std::vector<SaveIntraConnection> intraConnections;

        void Initialize(Drawmap * myDrawmap, DrawBezier* myDrawBezier, IntersectMap* myIntersectMap, MapIntraConnect* myIntraconnectMap);
        void Update();
        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void LateUpdate();

        //helper functions
        int* getStatus(); 
        SaveRoad* getRoad(int id);
        SaveIntraConnection* getIntraConnection(int id);

        void addRoad(SaveRoad road);
        void infoVisualizeRoad(int roadId, sf::Color color);

        SaveNode getSaveNodeFromMousePos(sf::Vector2f mousePos);
        bool checkInMapFromActualPos(sf::Vector2f actualPos);

        Map(sf::RenderWindow *rend);
        Map();

    private:
        sf::RectangleShape rect;
};

#endif