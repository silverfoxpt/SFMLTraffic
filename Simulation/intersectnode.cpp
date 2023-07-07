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

    //this->roadIdx.clear(); //release unneccessary space

    //find current displacement of the intersection on each node, compared to the beginning
    for (int i = 0; i < (int) this->myRoads.size(); i++) {
        sf::Vector2f lastPos = this->myRoads[i]->getNodePos(this->startNodeIdx[i]);
        sf::Vector2f lastStretch(this->posX - lastPos.x, this->posY - lastPos.y);

        this->displacements.push_back(this->myRoads[i]->getLengthFromStartToNode(this->startNodeIdx[i]) + Math::Length(lastStretch));
    }

    //for detection
    this->detecting = true;
}

void IntersectNode::Update() {
    //if shouldn't be detecting, stop!
    if (!this->detecting) {
        return;
    }

    // Find all cars on all roads which are closest to the intersection
    std::vector<std::pair<Car*, float>> cars;
    for (int i = 0; i < (int) this->myRoads.size(); i++) {
        auto compute = this->myRoads[i]->getFarthestCarBeforeDisplace(this->displacements[i]);
        if (compute.first != nullptr) {
            cars.push_back(compute);
        }
    }

    // If a car has already been accepted for intersection and it hasn't passed yet, do nothing
    if (this->currentlyAcceptedRoad >= 0) {
        auto road = this->myRoads[this->currentlyAcceptedRoad];

        //if that car is still passing by the intersection, do nothing and return
        int carIdx = road->findCarIdxOnRoad(this->currentAcceptedCar);
        if (carIdx != -1 && //car still on road
                (road->getTotalCarDisplace(carIdx) - CarInfo::carHalfLength < this->displacements[this->currentlyAcceptedRoad])) { //car hasn't passed yet
            return;
        }

        // Release blockade from all roads related to this node 
        for (int i = 0; i < (int) this->myRoads.size(); i++) {
            this->myRoads[i]->roadBlockedInfo.erase(this->UIUD);
        }

        this->currentAcceptedCar->SetColor(sf::Color::Red);

        this->currentAcceptedCar = nullptr;
        this->currentlyAcceptedRoad = -1;
    }

    // If there are no cars, do nothing
    if (cars.empty()) {
        return;
    }

    //if no car left on intersection, and new cars are available, continue
    // Get the car closest to this node -> THIS IS SCUFFED, NEED REVISE IN FUTURE
    Car* closestCar = cars[0].first;
    float closest = cars[0].second;
    int choosenIdx = 0;
    for (int i = 1; i < (int) cars.size(); i++) {
        if (cars[i].second > closest) {
            closestCar = cars[i].first;
            closest = cars[i].second;
            choosenIdx = i;
        }
    }

    closestCar->SetColor(sf::Color::Green);

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