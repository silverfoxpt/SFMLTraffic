#ifndef H_INTRACONNECT
#define H_INTRACONNECT

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

class MapIntraConnect {
    public: 
        sf::RenderWindow* myRend;
        Map* parent;

        //important stuffs from this
        int connectIdx1;
        int connectIdx2;

        MapIntraConnect(sf::RenderWindow* rend);
        MapIntraConnect() {} //default constructor

        void Input(sf::Event event);
        void Visualize(sf::Event event);
        void Initialize(Map* map);

        int* getConnect1() {return &this->connectIdx1;}
        int* getConnect2() {return &this->connectIdx2;}

};

#endif