#include "interconnect.h"

MapInterConnect::MapInterConnect(sf::RenderWindow* window) {
    this->myRend = window;
}

void MapInterConnect::Initialize(Map*  map) {
    this->parent = map;
}

void MapInterConnect::Input(sf::Event event) {

}

void MapInterConnect::Visualize(sf::Event event) {
    
} 