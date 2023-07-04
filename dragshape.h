#ifndef H_DRAGSHAPE
#define H_DRAGSHAPE

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class DragCircleShape {
public:
    DragCircleShape(sf::CircleShape shape) {
        m_shape = shape;
        m_isDragging = false;
    }

    void handleInput(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePos);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (m_shape.getGlobalBounds().contains(mousePosFloat)) {
                m_isDragging = true;
                m_offset = mousePosFloat - m_shape.getPosition();
            }
        }
        else {
            m_isDragging = false;
        }
    }

    void update(sf::RenderWindow& window) {
        if (m_isDragging) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePos);

            m_shape.setPosition(mousePosFloat - m_offset);
        }
    }

    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePos);
        return m_shape.getGlobalBounds().contains(mousePosFloat);
    }

    void drawShape(sf::RenderWindow& window) {
        window.draw(m_shape);
    }

private:
    sf::CircleShape m_shape;
    bool m_isDragging;
    sf::Vector2f m_offset;
};

#endif