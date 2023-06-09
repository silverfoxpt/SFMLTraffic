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
        
        //important stuff start here
        bool showWindow = false;
        int intersectIdx = -1; // this is the intersection idx for the traffic node

        //stuff that dealt with input -> DON'T FK WITH IT
        int choosenRoadIdx = 0;
        int choosenPhaseIdx = 0;

        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void Initialize(Map* map, IntersectMap* intersectMap);
        void Update();

        void AddTrafficPhasePopup();

        TrafficMap(sf::RenderWindow* rend);
        TrafficMap() {} //default constructor

        int* getChoosenRoadIdx() {return &this->choosenRoadIdx;}
        int* getChoosenPhaseIdx() {return &this->choosenPhaseIdx;}
};

#endif