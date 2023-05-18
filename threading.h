#ifndef H_THREADING
#define H_THREADING

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <thread>
#include <functional>

class Threading {
public:
    static void WaitThread(float waitTimeAsSeconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(waitTimeAsSeconds * 1000)));
    }
};

#endif