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

void GameObject::SetWorldPosition(sf::Vector2f position) {
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

void GameObject::SetTexture(sf::Texture* tex) {
    this->user.setTexture(tex);
}

void GameObject::Rotate(float eulerAngle) {
    this->rotation += eulerAngle;
    this->user.rotate(eulerAngle);
}

void GameObject::RotateToVector(sf::Vector2f toVec) {
    float degAng = std::fmod(std::fmod((360 - this->rotation), 360) + 90, 360);
    float toRad = degAng * 0.017453; //convert to rad, then minus 90 degs
    sf::Vector2f myVec(std::cos(toRad), std::sin(toRad));

    float pi = 3.1412;
    float angle = std::fmod(atan2(Math::Determinant(myVec, toVec), Math::DotProd(myVec, toVec)), 2*pi); //counterclockwise
    
    this->Rotate(360 - (angle * 180 / pi)); //clockwise
}

sf::Vector2f GameObject::GetPosition() {
    return this->position;
}

sf::Vector2f GameObject::GetNormalizeRotationVector() {
    float degAng = std::fmod(std::fmod((360 - this->rotation), 360) + 90, 360); //convert from clockwise -> counter clockwise, then shift to right 90 degs
    float toRad = degAng * 0.017453; //convert to rad
    sf::Vector2f myVec(std::cos(toRad), std::sin(toRad));

    float len = Math::Length(myVec);
    myVec.x /= len;
    myVec.y /= len;

    return myVec;
}
