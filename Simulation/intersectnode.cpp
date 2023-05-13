#include "intersectnode.h"

void IntersectNode::InitializeIntersectNode() {
    if (residentTile == nullptr) {std::cerr << "Need Tile!\n"; return;}

    //update position
    sf::Vector2f corner = this->residentTile->getCornerPos();
    int size = GameManager::tileSize;

    this->posX = corner.x + size * relativePos.x;
    this->posY = corner.y + size * relativePos.y;

    std::cout << this->residentTile->rowIdx << " " << this->residentTile->colIdx << '\n';

    //update road
    for (int x: roadIdx) {
        Road* road = residentTile->getRoad(x);
        myRoads.push_back(road);
    }

    this->roadIdx.clear(); //release unneccessary space

    //find current displacement of the intersection on each node, compared to the beginning
    for (int i = 0; i < (int) this->myRoads.size(); i++) {
        sf::Vector2f lastPos = this->myRoads[i]->getNodePos(this->startNodeIdx[i]);
        sf::Vector2f lastStretch(this->posX - lastPos.x, this->posY - lastPos.y);

        this->displacements.push_back(this->myRoads[i]->getLengthFromStartToNode(this->startNodeIdx[i]) + Math::Length(lastStretch));
    }
}

void IntersectNode::Update() {
    //find all cars on all roads, which is closest to intersection
    std::vector<std::pair<Car*, float>> cars;
    for (int i = 0; i < (int) this->myRoads.size(); i++) {
        cars.push_back(this->myRoads[i]->getFarthestCarBeforeDisplace(this->displacements[i]));
    }

    //find out of any of the cars match the profile of currently selected car to pass the intersection
    if (this->currentAcceptedCar != nullptr) { //if a car is (presumably) passing through my intersection
        bool found = false;
        for (const auto &p: cars) {
            if (p.first == this->currentAcceptedCar) {found = true; break;}
        }
        if (found) {return;}
    }

    //if, no car found, or the designated car already passed the intersection
    //release blockade from all road
}