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
        static constexpr float Exponent = 3;

        static float DotProd(sf::Vector2f a, sf::Vector2f b) {
            return a.x * b.x + a.y * b.y;
        }

        static float Determinant(sf::Vector2f a, sf::Vector2f b) {
            return a.x * b.y - a.y * b.x;
        }

        static float Length(sf::Vector2f a) {
            return std::sqrt(a.x * a.x + a.y * a.y);
        }

        static float Distance(sf::Vector2f a, sf::Vector2f b) {
             return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }

        static sf::Vector2f Middlepoint(sf::Vector2f a, sf::Vector2f b) {
            return sf::Vector2f((a.x + b.x) / 2, (a.y + b.y) / 2);
        }

        static sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t) {
            if (t <= 0) {return a;}
            if (t >= 1) {return b;}

            float x = a.x + (b.x - a.x) * t;
            float y = a.y + (b.y - a.y) * t;
            return sf::Vector2f(x, y);
        }

        static sf::Vector2f convertToFloatVec(sf::Vector2i a) {
            return sf::Vector2f(a.x, a.y);
        }

        //intersection of *segments*, NOT LINES
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
            float x = (d - b) / (a - c), y = a*x + b;

            //check if in both segments (previously we check for line)
            float mini = std::min(a1.x, a2.x), maxi = std::max(a1.x, a2.x);
            if (x < mini || x > maxi) { return nullRoad; }

            mini = std::min(b1.x, b2.x), maxi = std::max(b1.x, b2.x);
            if (x < mini || x > maxi) { return nullRoad; }

            //return
            return sf::Vector2i(x, y);
        }
};

#endif