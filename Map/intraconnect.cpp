#include "intraconnect.h"

MapIntraConnect::MapIntraConnect(sf::RenderWindow* rend) {
    this->myRend = rend;
}

void MapIntraConnect::Initialize(Map* map) {
    this->parent = map;
}

void MapIntraConnect::Input(sf::Event event) {

}

void MapIntraConnect::Visualize(sf::Event event) {
    
}