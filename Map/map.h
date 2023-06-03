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
#include "interconnect.h"
#include "trafficmap.h"

#include "nodes.h"

#include "../Simulation/gameManager.h"

class Drawmap;
class DrawBezier;
class IntersectMap;
class MapIntraConnect;
class MapInterConnect;
class TrafficMap;

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
        MapInterConnect* myInterconnectMap;
        TrafficMap* myTrafficMap;

        //important stuffs - must be updated if anything changes
        std::vector<SaveRoad> roads;
        std::vector<SaveIntersectingNode> intersections;
        std::vector<SaveIntraConnection> intraConnections;
        std::vector<SaveInterConnection> interConnections;
        std::vector<SaveRoadParticipantNode> roadParticpants;

        void Initialize(Drawmap * myDrawmap, DrawBezier* myDrawBezier, IntersectMap* myIntersectMap, MapIntraConnect* myIntraconnectMap, 
            MapInterConnect* myInterconnectMap, TrafficMap* myTrafficMap);
        void Update();
        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void LateUpdate();

        //helper functions
        int* getStatus(); 
        SaveRoad* getRoad(int id);
        SaveIntersectingNode* getIntersectingNode(int id);
        SaveIntraConnection* getIntraConnection(int id);
        SaveInterConnection* getInterConnection(int id);
        json getFullJson();

        void addRoad(SaveRoad road);
        void deleteRoad(int id);
        void infoVisualizeRoad(int roadId, sf::Color color);
        void clear();

        SaveNode getSaveNodeFromMousePos(sf::Vector2f mousePos);
        bool checkInMapFromActualPos(sf::Vector2f actualPos);

        Map(sf::RenderWindow *rend);
        Map();

    private:
        sf::RectangleShape rect;
};

#endif