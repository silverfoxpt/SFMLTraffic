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

        //intersect of segments
        static sf::Vector2i Intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2) {
            const sf::Vector2i nullRoad(-99999, -99999);

            // calculate slopes and y-intercepts
            const float slopeA = (a1.x - a2.x) == 0 ? std::numeric_limits<float>::infinity() : (a1.y - a2.y) / (a1.x - a2.x);
            const float yIntA = a1.y - slopeA * a1.x;
            const float slopeB = (b1.x - b2.x) == 0 ? std::numeric_limits<float>::infinity() : (b1.y - b2.y) / (b1.x - b2.x);
            const float yIntB = b1.y - slopeB * b1.x;

            // check if the segments are parallel
            const float epsilon = 1e-6f;
            if (std::abs(slopeA - slopeB) < epsilon) {
                return nullRoad;
            }

            // calculate intersection point
            const float x = std::isinf(slopeA) ? a1.x : (yIntB - yIntA) / (slopeA - slopeB);
            const float y = slopeA * x + yIntA;

            // check if intersection point is within both segments
            const bool inSegmentA = (x >= std::min(a1.x, a2.x)) && (x <= std::max(a1.x, a2.x));
            const bool inSegmentB = (x >= std::min(b1.x, b2.x)) && (x <= std::max(b1.x, b2.x));

            if (!inSegmentA || !inSegmentB) {
                return nullRoad;
            }

            return sf::Vector2i(x, y);
        }

};

#endif