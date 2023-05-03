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
    //conditional appearance
    if (this->parent->drawStatus == 2) {
        for (SaveIntersectingNode &node: this->parent->intersections) {
            sf::CircleShape a(5);
            a.setFillColor(sf::Color::Red);
            a.setOrigin(sf::Vector2f(5, 5));
            a.setPosition(node.posNode.mapPos);

            this->myRend->draw(a);
        }
    }
}