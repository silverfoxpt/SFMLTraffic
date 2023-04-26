#ifndef H_GAMEMANAGER
#define H_GAMEMANAGER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class GameManager {
    public:
        static sf::RenderWindow *rend;
        static float windowWidth;
        static float windowHeight;

        static sf::Vector2f convertWorldToScreen(sf::Vector2f world);
        static sf::Vector2f convertScreenToWorld(sf::Vector2f screen);

        static float deltaTime;
        static int tileSize;
};

#endif