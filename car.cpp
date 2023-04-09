#include "car.h"

void Car::Advance() {
    float currentVelocity = this->velocity + this->acceleration * GameManager::deltaTime;
    currentVelocity = std::max(currentVelocity, this->maxVelocity);

    float displacement = this->velocity * GameManager::deltaTime + 0.5 * this->acceleration * GameManager::deltaTime * GameManager::deltaTime;
    this->currentDisplacement += displacement;
    this->velocity = currentVelocity;

    //calculate new position
    sf::Vector2f pos = this->GetPosition();
    sf::Vector2f heading = this->GetNormalizeRotationVector();

    pos += heading * displacement;
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