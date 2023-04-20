#ifndef H_MATH
#define H_MATH

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class Math {
    public:
        static float DotProd(sf::Vector2f a, sf::Vector2f b) {
            return a.x * b.x + a.y * b.y;
        }

        static float Determinant(sf::Vector2f a, sf::Vector2f b) {
            return a.x * b.y - a.y * b.x;
        }

        static float Length(sf::Vector2f a) {
            return std::sqrt(a.x * a.x + a.y * a.y);
        }

        static float RotateToVector(sf::Vector2f toVec) {
            float degAng = std::fmod(std::fmod((360 - this->rotation), 360) + 90, 360);
            float toRad = degAng * 0.017453; //convert to rad, then minus 90 degs
            sf::Vector2f myVec(std::cos(toRad), std::sin(toRad));

            float pi = 3.1412;
            float angle = std::fmod(atan2(Math::Determinant(myVec, toVec), Math::DotProd(myVec, toVec)), 2*pi); //counterclockwise
            
            return 360 - (angle * 180 / pi); //clockwise angle
        }
};

#endif