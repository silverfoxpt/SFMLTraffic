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
#include "nodes.h"

#include "../Simulation/gameManager.h"

class Drawmap;

class Map {
    public:
        //initialize
        sf::RenderWindow* rend;
        int drawStatus          = 0;
        int size                = 200;
        sf::Vector2f offset     = sf::Vector2f(50, 50);

        //child class
        Drawmap* myDrawmap;

        //important stuffs
        std::vector<SaveRoad> roads;

        void Initialize(Drawmap * myDrawmap);
        void Update();
        void Input(sf::Event event);
        void Visualize(sf::Event event);

        int* getStatus(); 

        Map(sf::RenderWindow *rend);
        Map();

    private:
        sf::RectangleShape rect;
};

#endif