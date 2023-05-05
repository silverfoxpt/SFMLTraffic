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
    //other updates from children
    this->myIntersectMap->Update();
}

void Map::LateUpdate() {
    //late updates from children
    this->myIntersectMap->LateUpdate();
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
    //draw bounding box
    this->rend->draw(this->rect);

    //draw grid lines
    int additional = (float) this->size / (this->numGrid + 1);
    for (int i = 0; i < this->numGrid; i++) {
        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(this->offset.x, this->offset.y + (i+1) * additional), sf::Color(0, 0, 0, 100)),
            sf::Vertex(sf::Vector2f(this->offset.x + this->size, this->offset.y + (i+1) * additional), sf::Color(0, 0, 0, 100))
        };
        this->rend->draw(line , 2, sf::Lines);

        line[0] =  sf::Vertex(sf::Vector2f(this->offset.x + (i+1) * additional, this->offset.y), sf::Color(0, 0, 0, 100));
        line[1] =  sf::Vertex(sf::Vector2f(this->offset.x + (i+1) * additional, this->offset.y + this->size ), sf::Color(0, 0, 0, 100));
        this->rend->draw(line , 2, sf::Lines);
    }

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
                sf::Vertex(sf::Vector2f(begin.x, begin.y), sf::Color(0, 255, 0, 255)),
                sf::Vertex(sf::Vector2f(node.mapPos.x, node.mapPos.y), sf::Color(0, 255, 0, 255))
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

    for (int i = 0; i < (int) this->roads.size(); i++) {
        SaveRoad& road = this->roads[i];
        for (int j = 0; j < (int) addRoad.nodes.size() - 1; j++) {
            SaveNode b1 = addRoad.nodes[j], b2 = addRoad.nodes[j + 1];
            for (int k = 0; k < (int) road.nodes.size() - 1; k++) {
                SaveNode a1 = road.nodes[k], a2 = road.nodes[k + 1];
                auto intersection = Math::Intersect(a1.mapPos, a2.mapPos, b1.mapPos, b2.mapPos);
                if (intersection != nullRoad) {
                    SaveNode interNode = this->getSaveNodeFromMousePos(Math::convertToFloatVec(intersection));
                    SaveIntersectingNode newIntersection = {
                        interNode,
                        { i, static_cast<int>(this->roads.size()) },
                        { k, j }
                    };
                    newInter.push_back(newIntersection);
                }
            }
        }
    }

    // merge same intersections
    std::vector<SaveIntersectingNode> newUniqueInter;
    for (const auto& n2 : newInter) {
        bool found = false;
        for (auto& n1 : this->intersections) {
            if (Math::Distance(n1.posNode.mapPos, n2.posNode.mapPos) <= Math::Exponent) {
                n1.intersectingRoadIndex.insert(n1.intersectingRoadIndex.end(), n2.intersectingRoadIndex.begin(), n2.intersectingRoadIndex.end());
                n1.startNodeIdx.insert(n1.startNodeIdx.end(), n2.startNodeIdx.begin(), n2.startNodeIdx.end());
                found = true;
                break;
            }
        }
        if (!found) {
            newUniqueInter.push_back(n2);
        }
    }

    // add new unique intersections to map
    if (this->intersections.empty()) {
        this->intersections = newInter;
    } else {
        this->intersections.insert(this->intersections.end(), newUniqueInter.begin(), newUniqueInter.end());
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