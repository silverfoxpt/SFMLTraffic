#include "map.h"

void Map::Initialize() {
    this->rect.setFillColor(sf::Color::Transparent);
    this->rect.setOutlineColor(sf::Color::Red);
    this->rect.setOutlineThickness(3);

    this->rect.setPosition(this->offset);
}