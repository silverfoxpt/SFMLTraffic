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

        //if that car is still passing by the intersection, do nothing and return
        if ((std::find(road->currentCars.begin(), road->currentCars.end(), this->currentAcceptedCar) != road->currentCars.end()) &&
                (this->currentAcceptedCar->getCarBottom() >= this->displacements[this->currentlyAcceptedRoad])) {
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
    Car* closestCar = cars[0].first;
    float closest = cars[0].second;
    int choosenIdx = 0;
    for (int i = 1; i < (int) cars.size(); i++) {
        if (cars[i].second < closest) {
            closestCar = cars[i].first;
            closest = cars[i].second;
            choosenIdx = i;
        }
    }

    //set the car as accepted
    this->currentAcceptedCar = closestCar;
    this->currentlyAcceptedRoad = choosenIdx;

    //block all other roads
    for (int i = 0; i < (int) this->myRoads.size(); i++) {
        if (i == currentlyAcceptedRoad) {continue;}

        Road* blocky = this->myRoads[i];
        blocky->roadBlockedInfo[this->UIUD] = std::pair<Car*, float>(closestCar, this->displacements[i]);
    }
}