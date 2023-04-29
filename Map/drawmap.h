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

#include "map.h"
#include "nodes.h"

class Map;

class Drawmap {
    public:
        std::vector<SaveNode> nodes;

        sf::RenderWindow* myRend;
        Map* parent;

        Drawmap(sf::RenderWindow* rend);
        Drawmap();

        virtual void Input(sf::Event event);
        virtual void Visualize(sf::Event event);
        virtual void Initialize(Map* map);
};

#endif