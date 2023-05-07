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

void MapInterConnect::Submit() {
    int road = this->connectRoadId;
    int port = this->connectPortId;
    int side = this->connectSideId;
    int inout = this->inputOrOutput;

    int size = this->parent->roads.size();
    if (road < 0 || road >= size) {return;}

    SaveInterConnection newConnect = {road, port, side, inout};

    //check for duplication
    for (SaveInterConnection& connect: this->parent->interConnections) {
        if (newConnect.isEqual(connect)) {
            return;
        }
    }

    this->parent->interConnections.push_back(newConnect);
}

void MapInterConnect::MergeRoad(int id) {
    auto connect = this->parent->getInterConnection(id);
    auto road = this->parent->getRoad(connect->roadIdx);

    int side = connect->sideIdx;
    int port = connect->portIdx;

    sf::Vector2f pos;
    int additional = (float) this->parent->size / (this->parent->numGrid + 1);

    switch(side) {
        case 0: {
            pos = sf::Vector2f(this->parent->offset.x + port * additional, this->parent->offset.y); 
            break;
        } 
        case 1: {
            pos = sf::Vector2f(this->parent->offset.x + this->parent->size, this->parent->offset.y + port * additional); 
        }
        case 2: {
            pos = sf::Vector2f(this->parent->offset.x + port * additional, this->parent->offset.y + this->parent->size); 
            break;
        }
        case 3: {
            pos = sf::Vector2f(this->parent->offset.x, this->parent->offset.y + port * additional); 
            break;
        }
    }

    SaveNode newNode = this->parent->getSaveNodeFromMousePos(pos);
    if (connect->inputOrOutput == 0) { //input
        road->nodes[0] = newNode;
    } else { //output
        road->nodes[road->nodes.size()-1] = newNode;
    }
}

void MapInterConnect::VisualizeSelectedRoad(int id) {
    auto connect = this->parent->getInterConnection(id);

    this->parent->infoVisualizeRoad(connect->roadIdx, sf::Color::Yellow);

    //show port
    int side = connect->sideIdx;
    int port = connect->portIdx;

    sf::Vector2f pos;
    int additional = (float) this->parent->size / (this->parent->numGrid + 1);

    switch(side) {
        case 0: {
            pos = sf::Vector2f(this->parent->offset.x + port * additional, this->parent->offset.y); 
            DrawUtils::drawCircle(this->myRend, sf::Vector2f(pos.x, pos.y - 10), 3.5, sf::Color::Yellow);
            break;
        } 
        case 1: {
            pos = sf::Vector2f(this->parent->offset.x + this->parent->size, this->parent->offset.y + port * additional); 
            DrawUtils::drawCircle(this->myRend, sf::Vector2f(pos.x + 10, pos.y), 3.5, sf::Color::Yellow);
            break;
        }
        case 2: {
            pos = sf::Vector2f(this->parent->offset.x + port * additional, this->parent->offset.y + this->parent->size); 
            DrawUtils::drawCircle(this->myRend, sf::Vector2f(pos.x, pos.y + 10), 3.5, sf::Color::Yellow);
            break;
        }
        case 3: {
            pos = sf::Vector2f(this->parent->offset.x, this->parent->offset.y + port * additional); 
            DrawUtils::drawCircle(this->myRend, sf::Vector2f(pos.x - 10, pos.y), 3.5, sf::Color::Yellow);
            break;
        }
    }
}