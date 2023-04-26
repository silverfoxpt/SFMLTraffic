#include "map.h"

void Map::Initialize() {
    this->rect = sf::RectangleShape(sf::Vector2f(this->size, this->size));

    this->rect.setFillColor(sf::Color(255, 255, 255, 0));
    this->rect.setOutlineColor(sf::Color::Red);
    this->rect.setOutlineThickness(2);

    this->rect.setPosition(this->offset);
}

void Map::Update() {
    this->rend->draw(this->rect);
}

void Map::Input(sf::Event event) {
    // drawing
    if (this->drawStatus == 0) {
        this->myDrawmap.Input(event);
    }
}

int* Map::getStatus() {
    return &(this->drawStatus);
}