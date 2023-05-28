#ifndef H_TRAFFICMAP
#define H_TRAFFICMAP

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
#include "../dragshape.h"

class Map;
class IntersectMap;

class TrafficMap {
    public:
        sf::RenderWindow* myRend;

        Map* parent;
        IntersectMap* intersectMap;

        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void Initialize(Map* map, IntersectMap* intersectMap);
        void Update();

        TrafficMap(sf::RenderWindow* rend);
        TrafficMap() {} //default constructor
};

#endif