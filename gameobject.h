#ifndef H_GAMEOBJECT
#define H_GAMEOBJECT

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "gameManager.h"
#include "math.h"

class GameObject {
    public:
        sf::RectangleShape user;
        sf::Vector2f position;
        sf::Vector2f scale;
        float rotation; //range 0-360

        int width, height;

        GameObject(int width, int height);
        void SetWorldPosition(sf::Vector2f position);
        void SetScale(sf::Vector2f scale);
        void SetRotation(float rotation);
        void SetColor(sf::Color color);
        void SetTexture(sf::Texture* tex);

        void Rotate(float eulerAngle);
        void RotateToVector(sf::Vector2f vec);
        
        sf::Vector2f GetPosition();
        sf::Vector2f GetNormalizeRotationVector();

    private:
        
};

#endif