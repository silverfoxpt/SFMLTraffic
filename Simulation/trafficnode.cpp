#include "trafficnode.h"

void TrafficManager::Initialize(Tilemap* tilemap, IntersectManager* intersectManager) {
    for (int i = 0 ; i < (int) tilemap->rows; i++) {
        std::vector<TileTrafficManager> row; this->managers.push_back(row);

        for (int j = 0; j < (int) tilemap->cols; j++) {
            TileTrafficManager newManager;
            newManager.Initialize(tilemap->GetTile(i, j), intersectManager, tilemap->tileIds[i][j], i, j);
            this->managers[i].push_back(newManager);
        }
    }
    mainClock.restart();
}

void TrafficManager::Update() {
    for (auto &rows: this->managers) {
        for (auto &tileManager: rows) {
            tileManager.currentTimer += this->mainClock.getElapsedTime().asSeconds();
            tileManager.Update();
        }
    }
    mainClock.restart();
}

void TrafficManager::HardReset() {
    this->managers.clear();
    this->mainClock.restart();
}


void TileTrafficManager::Initialize(Tile* parentTile, IntersectManager* intersectManager, int tileId, int row, int col) {
    this->parentTile = parentTile;

    this->currentPhase = 0;
    this->currentTimer = 0;
    
    //get data from tileinfo.cpp
    this->phaseTimes = TileInfo::trafficPhases[tileId];
    auto parts = TileInfo::roadParticipants[tileId];

    //initialize traffic node for each intersect node IN THIS TILE
    TileIntersectManager* tileIntersectManager = intersectManager->getIntersectManagerTile(row, col);
    for (size_t i = 0; i < tileIntersectManager->nodes.size(); i++) {
        TrafficNode newTrafficNode;
        this->nodes.push_back(newTrafficNode);
    }

    //set data for each traffic node, mapped from road participants
    for (int i = 0; i < (int) parts.size(); i++) {
        //participant's data
        RoadParticipant part = parts[i];

        TrafficNode &myTrafficNode = this->nodes[part.intersectingNodeIdx]; //same idx for intersectNode and TrafficNode

        myTrafficNode.myRoad.push_back(this->parentTile->getRoad(part.roadInIntersectionIdx));
        myTrafficNode.roadToPhase.push_back(part.phaseIdx);
        myTrafficNode.allowedToProceed.push_back(false);
    }

    //finally, now initialize the traffic nodes
    int counter = 0;
    for (auto& trafficNode: this->nodes) {
        trafficNode.Initialize(parentTile, intersectManager->getIntersectNode(row, col, counter), this); //same idx for intersectNode and TrafficNode
        counter++;
    }
}

void TileTrafficManager::Update() {
    if (this->phaseTimes.size() <= 0) {return;} //no phase
    if (this->nodes.size() == 0) {return; } //no traffic node

    if (this->currentTimer >= this->phaseTimes[this->currentPhase]) {
        this->currentPhase++;

        if (currentPhase >= (int) this->phaseTimes.size()) {currentPhase = 0;}
        this->currentTimer = 0;
    }

    //update traffic light for each road here
    for (auto &trafficNode: this->nodes) {
        for (size_t i = 0; i < trafficNode.allowedToProceed.size(); i++) {
            trafficNode.allowedToProceed[i] = (trafficNode.roadToPhase[i] == this->currentPhase) ? true : false;
        }
        trafficNode.Update();
    }
}


void TrafficNode::Initialize(Tile* parentTile, IntersectNode* parentIntersectNode, TileTrafficManager* parentTrafficManager) {
    this->parentTile = parentTile;
    this->parentIntersectNode = parentIntersectNode;
    this->parentTrafficManager = parentTrafficManager;

    //optional: shut off the intersect node updates if this traffic node control smth
    if (this->myRoad.size() > 0) {
        //this->parentIntersectNode->detecting = false;
    }
}

void TrafficNode::Update() {
    int counter = 0;
    for (auto road: this->myRoad) {
        //get displacement until 
        int displacement = this->parentIntersectNode->displacements[counter];

        //check if this road is allowed in this phase
        bool allowed = this->allowedToProceed[counter];

        //find the car farthest before the intersection - a safety length - half the car's length (cause im stupid)
        float stopPos = displacement - CarInfo::safetyUntilTrafficStop - CarInfo::carHalfLength;
        auto farthest = road->getFarthestCarBeforeDisplace(stopPos + CarInfo::safetyBuffer); //buffer

        //allow/disallow to continue based on if road is closed due to traffic light(s) or not
        if (farthest.first != nullptr) {
            Car* car = farthest.first;
            
            //push in the car + length left of that car until the stop light
            if (allowed) {
                road->allowedCarsAtTraffic.push_back(std::pair<Car*, float>(car, std::max((float) 0, stopPos - farthest.second)));
            } else {
                road->blockedCarsAtTraffic.push_back(std::pair<Car*, float>(car, std::max((float) 0, stopPos - farthest.second)));
            }
        }
        counter++;
    }
}