#ifndef H_SFMLRANDOM
#define H_SFMLRANDOM

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class Rand {
    public:
        std::random_device dev;
        std::mt19937 rng;

        Rand() {
            this->rng = std::mt19937(dev());    
        }

        int RandomInt(int first, int last) {
            std::uniform_int_distribution<std::mt19937::result_type> randInt(first, last);
            return randInt(this->rng);
        }

        float RandomFloat01() {
            std::uniform_int_distribution<std::mt19937::result_type> randInt(0, 10000);
            return randInt(this->rng) / 10000.0;
        }
};

class Randomize {
    public:
        static Rand rand;
};

#endif