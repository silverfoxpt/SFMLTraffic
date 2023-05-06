#ifndef H_DRAWSHAPES
#define H_DRAWSHAPES

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class DrawUtils {
public:
    static void drawLine(sf::RenderWindow* window, sf::Vector2f start, sf::Vector2f end, sf::Color color, float thickness) {
        sf::Vertex line[] = {
            sf::Vertex(start, color),
            sf::Vertex(end, color)
        };

        line[0].color = color;
        line[1].color = color;

        line[0].position = start;
        line[1].position = end;

        window->draw(line, 2, sf::Lines);
    }

    static void drawCircle(sf::RenderWindow* window, sf::Vector2f center, float radius, sf::Color color, float thickness) {
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(color);
        circle.setOutlineThickness(thickness);
        circle.setPosition(center.x - radius, center.y - radius);

        window->draw(circle);
    }

    static void drawRectangle(sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f size, sf::Color color, float thickness) {
        sf::RectangleShape rectangle(size);
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(color);
        rectangle.setOutlineThickness(thickness);
        rectangle.setPosition(position);

        window->draw(rectangle);
    }
};

#endif