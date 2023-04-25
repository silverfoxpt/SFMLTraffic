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

class Map {
    public:
        sf::RenderWindow* rend;
        int drawStatus = 0;

        void Initialize();
        
        Map(sf::RenderWindow *rend) {
            this->rend = rend;   
        }
};

#endif