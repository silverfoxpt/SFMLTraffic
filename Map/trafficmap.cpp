#include "trafficmap.h"

TrafficMap::TrafficMap(sf::RenderWindow* rend) {
    this->myRend = rend;
}

void TrafficMap::Initialize(Map* map, IntersectMap* intersectMap) {
    this->parent = map;
    this->intersectMap = intersectMap;
}

void TrafficMap::Update() {

}

void TrafficMap::Input(sf::Event event) {

}

void TrafficMap::Visualize(sf::Event event) {

}

