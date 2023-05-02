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
#include "nodes.h"

#include "../Simulation/gameManager.h"

class Drawmap;
class DrawBezier;
class IntersectMap;

class Map {
    public:
        //initialize
        sf::RenderWindow* rend;
        int drawStatus          = 0;
        int size                = 400;
        sf::Vector2f offset     = sf::Vector2f(50, 50);

        //child class
        Drawmap* myDrawmap;
        DrawBezier* myDrawBezier;
        IntersectMap* myIntersectMap;

        //important stuffs
        std::vector<SaveRoad> roads;

        void Initialize(Drawmap * myDrawmap, DrawBezier* myDrawBezier, IntersectMap* myIntersectMap);
        void Update();
        void Input(sf::Event event);
        void Visualize(sf::Event event);

        int* getStatus(); 
        void addRoad(SaveRoad road);

        SaveNode getSaveNodeFromMousePos(sf::Vector2f mousePos);
        bool checkInMapFromActualPos(sf::Vector2f actualPos);

        Map(sf::RenderWindow *rend);
        Map();

    private:
        sf::RectangleShape rect;
};

#endif