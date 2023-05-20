#ifndef H_CARINFO
#define H_CARINFO

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class CarInfo {
    public:
        static float carLength;
        static float carHalfLength;

        static float minDesiredDistance;
        static float desiredVelocity;

        static float accelExponent;
        static float reactionTime;

        static float maxAccel;
        static float comfortDecel;

        static float slowDownFactor;
        static float lockSlowdownLength;
        static float lockStopLength;

        static float safetyInputJammedRoad;
        static float safetyIntersectionBlockadeRange;
};

#endif