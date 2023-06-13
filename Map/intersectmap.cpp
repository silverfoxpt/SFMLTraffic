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
        int counter = 0;
        for (auto& shape : this->shapes) {
            if (shape.isMouseOver(*this->myRend)) {
                //if mouse hovering over road, then add the roads to infoRoad vector.

                auto intersection = this->parent->intersections[counter];
                for (auto& roadIdx : intersection.intersectingRoadIndex) {
                    SaveRoad myRoad = this->parent->roads[roadIdx];
                    if (!myRoad.nodes.empty()) {
                        this->infoRoad.push_back(myRoad);
                    }
                }
            }
            counter++;
        }
    }
}

void IntersectMap::Input(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (this->intersectionStatus == 0) { //only apply if in intersection VIEWING & MODIFYING mode
            bool found = false;
            int counter = 0;
            for (auto& shape : this->shapes) {
                if (shape.isMouseOver(*this->myRend)) {
                    found = true;
                    break;
                }
                counter++;
            }

            if (found) {
                //delete choosen node
                this->parent->intersections.erase(this->parent->intersections.begin() + counter);

                //update everything in the SaveRoadParticipants
                std::vector<int> del; int c = 0;
                for (auto &part: this->parent->roadParticipants) {
                    if (part.intersectingNodeIdx == counter) { 
                        del.push_back(c);
                    } else if (part.intersectingNodeIdx > counter) { 
                        part.intersectingNodeIdx--;
                    }
                    c++;
                }
                std::reverse(del.begin(), del.end());
                for (int x: del) {
                    this->parent->roadParticipants.erase(this->parent->roadParticipants.begin() + x);
                }
            }
        }
    }
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