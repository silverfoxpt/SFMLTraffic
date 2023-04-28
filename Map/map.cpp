#include "map.h"

Map::Map(sf::RenderWindow* rend)  {
    this->rend = rend;   
}

Map::Map() {

}

void Map::Initialize(Drawmap* myDrawmap) {
    this->rect = sf::RectangleShape(sf::Vector2f(this->size, this->size));

    this->rect.setFillColor(sf::Color(255, 255, 255, 0));
    this->rect.setOutlineColor(sf::Color::Red);
    this->rect.setOutlineThickness(2);

    this->rect.setPosition(this->offset);

    this->myDrawmap = myDrawmap;
}

void Map::Update() {
    this->rend->draw(this->rect);
}

void Map::Input(sf::Event event) {
    // drawing
    if (this->drawStatus == 0) {
        this->myDrawmap->Input(event);
    }
}

void Map::Visualize(sf::Event event) {
    this->myDrawmap->Visualize(event);
}

int* Map::getStatus() {
    return &(this->drawStatus);
}