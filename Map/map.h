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
        int size = 200;
        sf::Vector2f offset = sf::Vector2f(50, 50);

        void Initialize();
        void Update();
        void Input();

        Map(sf::RenderWindow *rend) {
            this->rend = rend;   
        }

    private:
        sf::RectangleShape rect;
};

#endif