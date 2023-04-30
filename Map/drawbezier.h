#ifndef H_DRAWBEZIER
#define H_DRAWBEZIER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "drawmap.h"

#include "../Simulation/math.h"

class DrawBezier : public Drawmap {
    public:
        //for the bezier
        int numPoints = 50;
        bool clickedFirst = false;
        bool clickedSecond = false;

        bool isDraggingNode = false;

        SaveNode firstNode;
        SaveNode secondNode;
        sf::CircleShape bezierConfigure1;

        DrawBezier(sf::RenderWindow* rend) : Drawmap(rend) {
            this->myRend = rend;
        }

        DrawBezier() {} //default

        void Input(sf::Event event) override;
        virtual void Visualize(sf::Event event);
};

#endif