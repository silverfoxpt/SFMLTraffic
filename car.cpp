#include "car.h"

void Car::Advance() {
    float currentVelocity = this->velocity + this->acceleration * GameManager::deltaTime;

    float displacement = this->velocity * GameManager::deltaTime + 0.5 * this->acceleration * GameManager::deltaTime * GameManager::deltaTime;
    this->velocity = currentVelocity;

    //calculate new position
    sf::Vector2f pos = this->GetPosition();
    sf::Vector2f heading = this->GetNormalizeRotationVector();

    pos += heading * displacement;
    this->SetPosition(pos);
}