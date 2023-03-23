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

class Car : public GameObject {
    public:
        Car(int width, int height) : GameObject(width, height) {
            this->velocity = 0;
            this->acceleration = 0.01;
        }

        float velocity;
        float acceleration;

        void Advance();
};

#endif