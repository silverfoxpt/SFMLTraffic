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

void GameObject::SetPosition(sf::Vector2f position) {
    this->position = position;
    this->user.setPosition(GameManager::convertWorldToScreen(this->position));
}

void GameObject::SetRotation(float rotation) {
    this->rotation = rotation;
    this->user.setRotation(this->rotation);
}

void GameObject::SetColor(sf::Color col) {
    this->user.setFillColor(col);
}

void GameObject::SetScale(sf::Vector2f scale) {
    this->scale = scale;
    this->user.setScale(this->scale);
}

void GameObject::Rotate(float eulerAngle) {
    this->rotation += eulerAngle;
    this->user.rotate(eulerAngle);
}

void GameObject::RotateToVector(sf::Vector2f toVec) {
    float toRad = this->rotation * 0.017453 - 1.57079; //convert to rad, then minus 90 degs
    sf::Vector2f myVec(std::cos(toRad), std::sin(toRad));

    float pi = 3.1412;
    float angle = std::fmod(atan2(Determinant(myVec, toVec), DotProd(myVec, toVec)), 2*pi); //counterclockwise

    this->Rotate(360 - (angle * 180 / pi)); //clockwise
}

float DotProd(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

float Determinant(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.y - a.y * b.x;
}