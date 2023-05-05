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

void MapIntraConnect::VisualizeSelectedRoad(int id) {
    auto connect = this->parent->intraConnections[id];

    //draw line1
    SaveRoad road1 = this->parent->roads[connect.inputRoadIdx];
    SaveRoad road2 = this->parent->roads[connect.outputRoadIdx];

    //draw oppositing arrows
    this->drawYellowLine(this->myRend, road1.nodes[0].mapPos, road1.nodes[road1.nodes.size()-1].mapPos);
    this->drawYellowLine(this->myRend, road2.nodes[road1.nodes.size()-1].mapPos, road2.nodes[0].mapPos);
}

void MapIntraConnect::Submit() {
    int id1 = this->connectIdx1, id2 = this->connectIdx2;

    //check for crap
    if (id1 == id2) {return;}

    int size = this->parent->roads.size();
    if (id1 < 0 || id2 < 0 || id1 >= size || id2 >= size) {return;}

    SaveIntraConnection newConnect = {id1, id2};

    //check for duplication
    for (SaveIntraConnection& connect: this->parent->intraConnections) {
        if (newConnect.isEqual(connect)) {
            return;
        }
    }

    this->parent->intraConnections.push_back(newConnect);
}

//thanks chatgpt :))
void MapIntraConnect::drawYellowLine(sf::RenderTarget* target, const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    // Create a SFML vertex array with two vertices
    sf::VertexArray line(sf::Lines, 2);

    // Set the position and color of the first vertex
    line[0].position = point1;
    line[0].color = sf::Color::Yellow;

    // Set the position and color of the second vertex
    line[1].position = point2;
    line[1].color = sf::Color::Yellow;

    // Draw the line to the target
    target->draw(line);
}