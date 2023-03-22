#include "gameobject.h"

GameObject::GameObject(int width, int height) {
    this->position = sf::Vector2f(0, 0);
    this->rotation = 0;
    this->scale = sf::Vector2f(1, 1);

    //hardcoded
    this->width = width;
    this->height = height;

    this->user = sf::RectangleShape(sf::Vector2f(this->width, this->height));
    this->user.setFillColor(sf::Color::Red);
    this->user.setOrigin(sf::Vector2f(this->width/2, this->height/2));
    this->user.setRotation(this->rotation);
}