#ifndef H_CAR
#define H_CAR

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "gameobject.h"

class Car : GameObject {
    public:
        Car(int width, int height) : GameObject(width, height) {
            this->speed = 0;
            this->acceleration = 0;
        }

        float speed;
        float acceleration;
};

#endif