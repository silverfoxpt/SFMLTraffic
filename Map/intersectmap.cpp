#include "intersectmap.h"

IntersectMap::IntersectMap(sf::RenderWindow* rend) {
    this->myRend = rend;
}

void IntersectMap::Initialize(Map* myMap) {
    this->parent = myMap;
}

void IntersectMap::Update() {
    this->circles.clear();
    this->shapes.clear();
    this->infoRoad.clear();

    for (SaveIntersectingNode &node: this->parent->intersections) {
        sf::CircleShape a(5);
        a.setFillColor(sf::Color::Red);
        a.setOrigin(sf::Vector2f(5, 5));
        a.setPosition(node.posNode.mapPos);

        this->circles.push_back(a);

        DragShape newShape(&this->circles[this->circles.size()-1]);
        this->shapes.push_back(newShape);
    }

    if (this->intersectionStatus == 0) { //only apply if in intersection VIEWING mode
        for (auto& shape : this->shapes) {
            if (shape.isMouseOver(*this->myRend)) {
                //if mouse hovering over road, then add the roads to infoRoad vector

                for (auto& intersection : this->parent->intersections) {
                    for (auto& roadIdx : intersection.intersectingRoadIndex) {
                        SaveRoad myRoad = this->parent->roads[roadIdx];
                        if (!myRoad.nodes.empty()) {
                            this->infoRoad.push_back(myRoad);
                        }
                    }
                }
            }
        }
    }
}

void IntersectMap::Input(sf::Event event) {
    
}

void IntersectMap::LateUpdate() {

}

void IntersectMap::Visualize(sf::Event event) {
    for (auto& myRoad: this->infoRoad) {
        SaveNode cur = myRoad.nodes[0];
        for (int i = 1; i < (int) myRoad.nodes.size(); i++) {
            SaveNode cur2 = myRoad.nodes[i];
            
            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(cur.mapPos.x, cur.mapPos.y), sf::Color::Yellow),
                sf::Vertex(sf::Vector2f(cur2.mapPos.x, cur2.mapPos.y), sf::Color::Yellow)
            };
            this->myRend->draw(line , 2, sf::Lines);

            cur = cur2;
        }
    }
    
    //conditional appearance
    if (this->parent->drawStatus == 2) {
        for (auto& shape: this->shapes) {
            shape.drawShape(*this->myRend);
        }
    }
}