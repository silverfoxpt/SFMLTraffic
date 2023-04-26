#ifndef H_DRAWMAP
#define H_DRAWMAP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../Simulation/tile.h"
#include "map.h"

class Map;

class Drawmap {
    public:
        bool isDrawing;
        std::vector<Node> nodes;

        sf::RenderWindow* myRend;
        Map* parent;

        Drawmap(sf::RenderWindow* rend, Map* par);
        Drawmap() {} //default constructor
        void Input(sf::Event event);
};

#endif