#include "map.h"

Map::Map(sf::RenderWindow* rend)  {
    this->rend = rend;   
}

Map::Map() {

}

void Map::Initialize(Drawmap* myDrawmap, DrawBezier* myDrawBezier, IntersectMap* myIntersectMap) {
    this->rect = sf::RectangleShape(sf::Vector2f(this->size, this->size));

    this->rect.setFillColor(sf::Color(255, 255, 255, 0));
    this->rect.setOutlineColor(sf::Color::Red);
    this->rect.setOutlineThickness(2);

    this->rect.setPosition(this->offset);

    //add children
    this->myDrawmap = myDrawmap;
    this->myDrawBezier = myDrawBezier;
    this->myIntersectMap = myIntersectMap;
}

void Map::Update() {
    this->rend->draw(this->rect);
}

void Map::Input(sf::Event event) {
    // drawing
    if (this->drawStatus == 0) {
        this->myDrawmap->Input(event);
    } else if (this->drawStatus == 1) {
        this->myDrawBezier->Input(event);
    } else if (this->drawStatus == 2) {
        this->myIntersectMap->Input(event);
    }
}

void Map::Visualize(sf::Event event) {
    //visualize for sub-map event
    this->myDrawmap->Visualize(event);
    this->myDrawBezier->Visualize(event);
    //this->myIntersectMap->Visualize(event);

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

    //visualize for sub-map event - postmain for layering purposes
    this->myIntersectMap->Visualize(event);
}

int* Map::getStatus() {
    return &(this->drawStatus);
}

void Map::addRoad(SaveRoad addRoad) {
    //find new intersection(s)
    std::vector<SaveIntersectingNode> newInter;
    sf::Vector2i nullRoad(-99999, -99999);

    int mainIdx = 0;
    for (SaveRoad& road: this->roads) {
        for (int i = 0; i < (int) road.nodes.size()-1; i++) {
            SaveNode a1 = road.nodes[i], a2 = road.nodes[i+1];

            for (int j = 0; j < (int) addRoad.nodes.size()-1; j++) {
                SaveNode b1 = addRoad.nodes[j], b2 = addRoad.nodes[j+1];

                auto intersection = Math::Intersect(a1.mapPos, a2.mapPos, b1.mapPos, b2.mapPos);
                if (intersection == nullRoad) {continue;}

                SaveNode interNode = this->getSaveNodeFromMousePos(Math::convertToFloatVec(intersection));

                SaveIntersectingNode newIntersection;
                newIntersection.posNode = interNode;
                newIntersection.intersectingRoadIndex.push_back(mainIdx);
                newIntersection.intersectingRoadIndex.push_back(road.nodes.size());
                newIntersection.startNodeIdx.push_back(i);
                newIntersection.startNodeIdx.push_back(j);

                newInter.push_back(newIntersection);
            }
        }   
        mainIdx++;
    }

    //merge same intersection
    std::vector<SaveIntersectingNode> newUniqueInter;
    for (int i = 0; i < (int) this->intersections.size(); i++) {
        for (int j = 0; j < (int) newInter.size(); j++) {
            SaveIntersectingNode n1 = this->intersections[i];
            SaveIntersectingNode n2 = newInter[j];

            float len = Math::Distance(n1.posNode.mapPos, n2.posNode.mapPos);

            //group da nodes together :v
            if (len <= Math::Exponent) {
                for (int k = 0; k < n2.intersectingRoadIndex.size(); k++) {
                    this->intersections[i].intersectingRoadIndex.push_back(n2.intersectingRoadIndex[k]);
                    this->intersections[i].startNodeIdx.push_back(n2.startNodeIdx[k]);
                }
            } else {
                newUniqueInter.push_back(n2);
            }
        }
    }
    if (this->intersections.size() == 0) {
        newUniqueInter = newInter;
    }

    //add new unique intersection to map
    for (SaveIntersectingNode node: newUniqueInter) {
        this->intersections.push_back(node);
    }

    //add road
    this->roads.push_back(addRoad);
}

SaveNode Map::getSaveNodeFromMousePos(sf::Vector2f mousePos) {
    //create node
    sf::Vector2f relativePos((mousePos.x - this->offset.x) / GameManager::tileSize, (mousePos.y - this->offset.y) / GameManager::tileSize);
    sf::Vector2f actualPos(mousePos.x, mousePos.y);

    SaveNode newNode;
    newNode.mapPos = actualPos;
    newNode.relativePos = relativePos;

    return newNode;
}

bool Map::checkInMapFromActualPos(sf::Vector2f actualPos) {
    //check if node in box
    if (actualPos.x < this->offset.x || actualPos.y < this->offset.y ||
        actualPos.x > this->offset.x + this->size || 
        actualPos.y > this->offset.y + this->size
    ) 
    {
        return false;
    }
    return true;
}