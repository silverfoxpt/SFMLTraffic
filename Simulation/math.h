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

        static sf::Vector2f spinPoint(const sf::Vector2f point, const sf::Vector2f center, float angleDegrees) {
            sf::Transform transform;
            transform.translate(center);
            transform.rotate(angleDegrees);
            transform.translate(-center);

            return transform.transformPoint(point);
        }

        static sf::Vector2f convertToFloatVec(sf::Vector2i a) {
            return sf::Vector2f(a.x, a.y);
        }

        static bool CheckSimilarPoint(sf::Vector2f a1, sf::Vector2f a2, bool debug = false) {
            const float epsilon = 0.001;
            if (std::abs(a1.x - a2.x) <= epsilon && std::abs(a1.y - a2.y) <= epsilon) {
                if (debug) {
                    //std::cout << "Similar!" << '\n';
                }
                return true;
            }
            return false;
        }

        static bool CheckSimilarNumber(float a, float b) {
            const float epsilon = 0.001;
            if (std::abs(a - b) <= epsilon) {
                return true;
            }
            return false;
        }

        //intersect of segments
        //https://en.wikipedia.org/wiki/Line–line_intersection#Given_two_points_on_each_line 
        //stop doing stupid stuffs :)
        /*static sf::Vector2i Intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2, bool debug = false) {
            const sf::Vector2i nullRoad(-99999, -99999);

            //check same endpoint(s)
            if (CheckSimilarPoint(a1, b1, debug)) {return sf::Vector2i(a1.x, a1.y);}
            if (CheckSimilarPoint(a1, b2, debug)) {return sf::Vector2i(a1.x, a1.y);}
            if (CheckSimilarPoint(a2, b1, debug)) {return sf::Vector2i(a2.x, a2.y);}
            if (CheckSimilarPoint(a2, b2, debug)) {return sf::Vector2i(a2.x, a2.y);}

            // calculate slopes and y-intercepts
            const float slopeA = (a1.x - a2.x) == 0 ? std::numeric_limits<float>::infinity() : (a1.y - a2.y) / (a1.x - a2.x);
            const float yIntA = (slopeA == std::numeric_limits<float>::infinity()) ? 0 : (a1.y - slopeA * a1.x);
            const float slopeB = (b1.x - b2.x) == 0 ? std::numeric_limits<float>::infinity() : (b1.y - b2.y) / (b1.x - b2.x);
            const float yIntB = (slopeB == std::numeric_limits<float>::infinity()) ? 0 : (b1.y - slopeB * b1.x);

            // check if the segments are parallel
            const float epsilon = 1e-6f;
            if ((slopeA == std::numeric_limits<float>::infinity() && slopeB == std::numeric_limits<float>::infinity()) || 
                (slopeA != std::numeric_limits<float>::infinity() && slopeB != std::numeric_limits<float>::infinity() && std::abs(slopeA - slopeB) < epsilon)) 
            {
                //std::cout << "parralel" << '\n';
                return nullRoad;
            }

            // calculate intersection point
            const float x = (slopeA == std::numeric_limits<float>::infinity()) ? a1.x : (yIntB - yIntA) / (slopeA - slopeB);
            const float y = slopeA * x + yIntA;

            // check if intersection point is within both segments
            const bool inSegmentA = ((x >= std::min(a1.x, a2.x)) && (x <= std::max(a1.x, a2.x))) || ((CheckSimilarNumber(a1.x, a2.x) && CheckSimilarNumber(x, a1.x)));
            const bool inSegmentB = ((x >= std::min(b1.x, b2.x)) && (x <= std::max(b1.x, b2.x))) || ((CheckSimilarNumber(b1.x, b2.x) && CheckSimilarNumber(x, b1.x)));

            const bool inSegmentA2 = ((y >= std::min(a1.y, a2.y)) && (y <= std::max(a1.y, a2.y))) || ((CheckSimilarNumber(a1.y, a2.y) && CheckSimilarNumber(y, a1.y)));
            const bool inSegmentB2 = ((y >= std::min(b1.y, b2.y)) && (y <= std::max(b1.y, b2.y))) || ((CheckSimilarNumber(b1.y, b2.y) && CheckSimilarNumber(y, b1.y)));

            if ((!inSegmentA) || (!inSegmentB) || (!inSegmentA2) || (!inSegmentB2)) {
                if (debug) {
                    std::cout << "Debug: " << inSegmentA << " " << inSegmentB << " " << inSegmentA2 << " " << inSegmentB2 << " " << x << " " << y << '\n';
                }
                return nullRoad;
            }

            return sf::Vector2i(x, y);
        }*/

        /*static sf::Vector2i Intersect(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4) {
            float x1 = p1.x, y1 = p1.y;
            float x2 = p2.x, y2 = p2.y;
            float x3 = p3.x, y3 = p3.y;
            float x4 = p4.x, y4 = p4.y;

            float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

            // Check if lines are parallel or coincident
            const float epsilon = 1e-6; // Adjust epsilon value as needed
            if (std::abs(denominator) < epsilon) {
                return sf::Vector2i(-99999, -99999);
            }

            float numerator1 = (x1 * y2 - y1 * x2);
            float numerator2 = (x3 * y4 - y3 * x4);

            float x = (numerator1 * (x3 - x4) - (x1 - x2) * numerator2) / denominator;
            float y = (numerator1 * (y3 - y4) - (y1 - y2) * numerator2) / denominator;

            // Check if intersection point lies within both line segments
            if (x < std::min(x1, x2) || x > std::max(x1, x2) || y < std::min(y1, y2) || y > std::max(y1, y2) ||
                x < std::min(x3, x4) || x > std::max(x3, x4) || y < std::min(y3, y4) || y > std::max(y3, y4)) {
                return sf::Vector2i(-99999, -99999);
            }

            return sf::Vector2i(static_cast<int>(x), static_cast<int>(y));
        }*/

        static sf::Vector2i Intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2, bool debug = false) {
            float x1 = a1.x, y1 = a1.y;
            float x2 = a2.x, y2 = a2.y;
            float x3 = b1.x, y3 = b1.y;
            float x4 = b2.x, y4 = b2.y;

            float t1 = (x1-x3) * (y3-y4) - (y1-y3) * (x3-x4);
            float t2 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
            float t = t1/t2;

            float u1 = (x1-x3) * (y1-y2) - (y1-y3) * (x1-x2);
            float u2 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
            float u = u1/u2;

            if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
                return sf::Vector2i(x1 + t*(x2-x1), y1 + t*(y2-y1));
            }
            return sf::Vector2i(-99999, -99999);
        }
};

#endif