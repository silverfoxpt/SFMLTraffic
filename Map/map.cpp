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
    //visualize for sub-map event
    this->myDrawmap->Visualize(event);

    //visualize for main

    //draw all road
    for (auto &road : this->roads) {
        sf::Vector2f begin; int c = 0;
        for (auto &node: road.nodes) {
            if (c == 0) {
                begin = node.mapPos; c++; continue;
            }

            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(begin.x, begin.y), sf::Color::Green),
                sf::Vertex(sf::Vector2f(node.mapPos.x, node.mapPos.y), sf::Color::Green)
            };
            this->rend->draw(line , 2, sf::Lines);
            begin = node.mapPos;
        }
    }
}

int* Map::getStatus() {
    return &(this->drawStatus);
}

void Map::addRoad(SaveRoad road) {
    this->roads.push_back(road);
}