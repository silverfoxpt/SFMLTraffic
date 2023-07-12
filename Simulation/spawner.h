#ifndef H_SPAWNER
#define H_SPAWNER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "car.h"
#include "tile.h"
#include "gameManager.h"

class Spawner {
    public:
        int currentNumOfCar;
        std::vector<Car> cars;
        std::vector<bool> carActive;

        std::vector<Road*> startableRoads;

        //from other
        Tilemap* tilemap;
        sf::RenderWindow* window;

        Spawner();

        void Initialize(Tilemap* tilemap, sf::RenderWindow* window);
        void Update();
        void HardReset();
        void Visualize();

        Car* getCar(int idx);

};

#endif
