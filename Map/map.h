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

#include "../Simulation/gameManager.h"

class Drawmap;
//class SaveNode;
//class SaveRoad;

class Map {
    public:
        //initialize
        sf::RenderWindow* rend;
        int drawStatus = 0;
        int size = 200;
        sf::Vector2f offset = sf::Vector2f(50, 50);

        //child class
        Drawmap* myDrawmap;

        //important stuffs
        //std::vector<SaveRoad> roads;

        void Initialize();
        void Update();
        void Input(sf::Event event);
        void Visualize();

        int* getStatus(); 

        Map(sf::RenderWindow *rend) {
            this->rend = rend;   
        }
        Map() {} //default

    private:
        sf::RectangleShape rect;
};

#endif