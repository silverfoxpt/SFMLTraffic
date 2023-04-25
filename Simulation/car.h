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
#include "carInfo.h"

class Car : public GameObject {
    public:
        Car(int width, int height) : GameObject(width, height) {
            this->velocity = 0;
            this->acceleration = CarInfo::maxAccel;
            this->maxVelocity = CarInfo::desiredVelocity;
            this->currentDisplacement = 0;
        }

        float velocity;
        float acceleration;

        float maxVelocity;
        float currentDisplacement;

        void SetAcceleration(float acc);
        void SetVelocity(float velocity);
        void Advance();
        void ResetCurrentDisplacement();

        float getCarTop();
        float getCarBottom();
        float getDifferenceInPos(Car* behind, Car* forward);


};

#endif