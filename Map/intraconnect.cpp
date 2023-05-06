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
    auto connect = this->parent->getIntraConnection(id);

    //draw
    this->parent->infoVisualizeRoad(connect->inputRoadIdx, sf::Color::Yellow);
    this->parent->infoVisualizeRoad(connect->outputRoadIdx, sf::Color::Yellow);
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

void MapIntraConnect::MergeRoad(int id1, int id2) {
    auto road1 = this->parent->getRoad(id1);
    auto road2 = this->parent->getRoad(id2);
    if (road1 == nullptr || road2 == nullptr) {std::cerr << "Road not found : MergeRoad\n"; return;}

    SaveNode first = road1->nodes.back();
    SaveNode sec = road2->nodes.front();

    sf::Vector2f mid = Math::Middlepoint(first.mapPos, sec.mapPos);
    SaveNode new1 = this->parent->getSaveNodeFromMousePos(mid), new2 = new1;

    road1->nodes[road1->nodes.size()-1] = new1;
    road2->nodes[0] = new2;
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
