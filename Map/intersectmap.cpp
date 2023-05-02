#include "intersectmap.h"

IntersectMap::IntersectMap(sf::RenderWindow* rend) {
    this->myRend = rend;
}

void IntersectMap::Initialize(Map* myMap) {
    this->parent = myMap;
}

void IntersectMap::Input(sf::Event event) {

}

void IntersectMap::Visualize(sf::Event event) {

}