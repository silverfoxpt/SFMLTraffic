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

#include "drawmap.h"

class Drawmap;

class Map {
    public:
        sf::RenderWindow* rend;
        int drawStatus = 0;
        int size = 200;
        sf::Vector2f offset = sf::Vector2f(50, 50);

        //child class
        Drawmap myDrawmap;

        void Initialize();
        void Update();
        void Input(sf::Event event);

        int* getStatus(); 

        Map(sf::RenderWindow *rend) {
            this->rend = rend;   
            this->myDrawmap = Drawmap(rend, this);
        }
        Map() {} //default

    private:
        sf::RectangleShape rect;
};

#endif