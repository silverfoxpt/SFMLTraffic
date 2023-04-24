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

        static sf::Vector2i Intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2) {
            sf::Vector2i nullRoad(-99999, -99999);

            bool line1Up = false, line2Up = false;
            float a = -1, b = a, c = b, d = c;

            if (a1.x == a2.x) {
                line1Up = true;
            } else {
                a = (a1.y - a2.y) / (a1.x - a2.x);
                b = a1.y - a * a1.x;
            }

            if (b1.x == b2.x) {
                line2Up = true;
            } else {
                c = (b1.y - b2.y) / (b1.x - b2.x);
                d = b1.y - c * b1.x;
            }
            
            //special case when one or both lines is parallel with Oy
            if (line1Up) {
                if (line2Up) {
                    return nullRoad;
                } else {
                    return sf::Vector2i(a1.x, c * a1.x + d);
                }
            }

            if (line2Up) {
                return sf::Vector2i(b1.x, a * b1.x + b);
            }

            // check state of line -> parallel or similar
            if (a == c) {
                return nullRoad; 
            }

            //actually calculate stuff
            int x = (d - b) / (a - c), y = a*x + b;

            //check if in both segments (previously we check for line)
            int mini = std::min(a1.x, a2.x), maxi = std::max(a1.x, a2.x);
            if (x < mini || x > maxi) { return nullRoad; }

            mini = std::min(b1.x, b2.x), maxi = std::max(b1.x, b2.x);
            if (x < mini || x > maxi) { return nullRoad; }

            //return
            return sf::Vector2i(x, y);
        }
};

#endif