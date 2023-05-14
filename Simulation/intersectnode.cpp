#include "intersectnode.h"

void IntersectNode::InitializeIntersectNode() {
    if (residentTile == nullptr) {std::cerr << "Need Tile!\n"; return;}

    //update position
    sf::Vector2f corner = this->residentTile->getCornerPos();
    int size = GameManager::tileSize;

    this->posX = corner.x + size * relativePos.x;
    this->posY = corner.y + size * relativePos.y;

    //std::cout << this->residentTile->rowIdx << " " << this->residentTile->colIdx << '\n';

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
    // Find all cars on all roads which are closest to the intersection
    std::vector<std::pair<Car*, float>> cars;
    for (int i = 0; i < (int) this->myRoads.size(); i++) {
        cars.push_back(this->myRoads[i]->getFarthestCarBeforeDisplace(this->displacements[i]));
    }

    // If a car has already been accepted for intersection and it hasn't passed yet, do nothing
    if (this->currentlyAcceptedRoad >= 0) {
        auto road = this->myRoads[this->currentlyAcceptedRoad];

        if (std::find(road->carOnNode.begin(), road->carOnNode.end(), this->currentAcceptedCar) != road->carOnNode.end() &&
                this->currentAcceptedCar->getCarBottom() >= this->displacements[this->currentlyAcceptedRoad]) {
            return;
        }

        // Release blockade from all roads related to this node 
        for (int i = 0; i < (int) this->myRoads.size(); i++) {
            this->myRoads[i]->roadBlockedInfo.erase(this->UIUD);
        }

        this->currentAcceptedCar = nullptr;
        this->currentlyAcceptedRoad = -1;
    }

    // If there are no cars, do nothing
    if (cars.empty()) {
        return;
    }

    //if no car left on intersection, and new cars are available, continue
    // Get the car closest to this node
    // Car* closestCar
}