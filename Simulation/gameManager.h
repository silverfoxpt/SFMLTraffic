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

        static float deltaTime;
        static int tileSize;

        static int totalNumOfCar;

        static sf::Vector2u mainWindowSize;
        static sf::Vector2u mapWindowSize;
        static sf::Vector2u originalResolution;

        static sf::Vector2f convertWorldToScreen(sf::Vector2f world);
        static sf::Vector2f convertScreenToWorld(sf::Vector2f screen);

        static void InitializeWindowWithResolution(sf::RenderWindow* mainWindow, sf::RenderWindow* mapWindow);
};

#endif