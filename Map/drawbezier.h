#ifndef H_DRAWBEZIER
#define H_DRAWBEZIER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "map.h"
#include "nodes.h"

#include "../Simulation/math.h"

class Map;

class DrawBezier {
    public:
        //normal stuffs
        std::vector<SaveNode> nodes;

        sf::RenderWindow* myRend;
        Map* parent;

        //for the bezier
        int numPoints = 8;
        bool clickedFirst = false;
        bool clickedSecond = false;

        bool isDraggingNode1 = false;
        //bool isCubic = false;

        SaveNode firstNode;
        SaveNode secondNode;
        sf::CircleShape bezierConfigure1;

        DrawBezier(sf::RenderWindow* rend) {
            this->myRend = rend;
        }

        DrawBezier() {} //default

        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void Initialize(Map* myMap);
        //void Dragging();
};

#endif