#include "car.h"

void Car::Advance() {
    float currentVelocity       = std::min(this->velocity + this->acceleration * GameManager::deltaTime, this->maxVelocity);
    float currentDisplacement   = this->velocity * GameManager::deltaTime + 0.5 * this->acceleration * GameManager::deltaTime * GameManager::deltaTime;

    if (currentVelocity < 0) {
        currentDisplacement = -0.5 * (this->velocity * this->velocity / this->acceleration);
        currentVelocity = 0;
    } 
    std::cout << currentVelocity << '\n';

    this->currentDisplacement   += currentDisplacement;
    this->velocity              = currentVelocity;

    //calculate new position
    sf::Vector2f pos        = this->GetPosition();
    sf::Vector2f heading    = this->GetNormalizeRotationVector();

    pos                     += heading * currentDisplacement;
    this->SetWorldPosition(pos);
}

void Car::SetAcceleration(float acc) {
    this->acceleration = acc;
}

void Car::SetVelocity(float velocity) {
    this->velocity = velocity;
}

void Car::ResetCurrentDisplacement() {
    this->currentDisplacement = 0;
}


float Car::getCarTop() {
    return this->currentDisplacement + CarInfo::carHalfLength;
}

float Car::getCarBottom() {
    return this->currentDisplacement - CarInfo::carHalfLength;
}

float Car::getDifferenceInPos(Car* behind, Car* front) {
    return front->currentDisplacement - behind->currentDisplacement;
}