#ifndef H_INTERCONNECTMAP
#define H_INTERCONNECTMAP

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

class Map;

class MapInterConnect {
    public:
        //number of ports
        const int minPort = 1;
        const int maxPort = 20;

        sf::RenderWindow* myRend;
        Map* parent;

        //important stuffs from this
        int connectRoadId;
        int connectPortId = 1; //counted left to right and top to bottom
        int connectSideId; // 0 top, 1 right, 2 down, 3 left
        int inputOrOutput; //input 0, output 1

        MapInterConnect(sf::RenderWindow* rend);
        MapInterConnect() {} //default constructor

        void Input(sf::Event event);
        void Visualize(sf::Event event = sf::Event());
        void Initialize(Map* map);

        int* getRoadId() {return &this->connectRoadId;}
        int* getConnectPort() {return &this->connectPortId;}
        int* getConnectSide() {return &this->connectSideId;}
        int* getInputOrOutput() {return &this->inputOrOutput; }
};

#endif