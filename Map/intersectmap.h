#ifndef H_INTERSECTMAP
#define H_INTERSECTMAP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "nodes.h"
#include "map.h"

class Map;

class IntersectMap {
    public:
        sf::RenderWindow* myRend;

        Map* parent;

        IntersectMap(sf::RenderWindow* rend);
        IntersectMap() {} //default constructor

        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void Initialize(Map* map);
};

#endif