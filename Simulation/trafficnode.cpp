#include "trafficnode.h"

void TrafficManager::Initialize(Tilemap* tilemap, IntersectManager* intersectManager) {
    for (int i = 0 ; i < (int) tilemap->rows; i++) {
        std::vector<TileTrafficManager> row; this->managers.push_back(row);

        for (int j = 0; j < (int) tilemap->cols; j++) {
            TileTrafficManager newManager;
            newManager.Initialize(tilemap->GetTile(i, j), intersectManager, tilemap->tileIds[i][j]);
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

void TileTrafficManager::Initialize(Tile* parentTile, IntersectManager* intersectManager, int tileId) {
    this->currentPhase = 0;
    this->currentTimer = 0;
    
    //get data from tileinfo.cpp
    this->phaseTimes = TileInfo::trafficPhases[tileId];
    auto parts = TileInfo::roadParticipants[tileId];

    //set data for each traffic node, mapped from road participants
    for (int i = 0; i < (int) parts.size(); i++) {
        //participant's data
        RoadParticipant part = parts[i];

        TrafficNode newTrafficNode;
        newTrafficNode.Initialize(parentTile, intersectManager->getIntersectNode(part.intersectingNodeIdx), this);
        newTrafficNode.myRoad.push_back(this->parentTile->getRoad(part.roadInIntersectionIdx));
        newTrafficNode.roadToPhase.push_back(part.phaseIdx);
        newTrafficNode.allowedToProceed.push_back(false);

        this->nodes.push_back(newTrafficNode);
    }
}

void TileTrafficManager::Update() {
    if (this->phaseTimes.size() <= 0) {return;} //no phase
    if (this->nodes.size() == 0) {return; } //no traffic node

    if (this->currentTimer >= this->phaseTimes[this->currentPhase]) {
        this->currentPhase++;

        if (currentPhase >= (int) this->phaseTimes.size()) {currentPhase = 0;}
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

    //initialize index in intersect node
    for (int i = 0; i < (int) this->myRoad.size(); i++) {
        int idx = (std::find(this->parentIntersectNode->myRoads.begin(), this->parentIntersectNode->myRoads.end(), this->myRoad[i]) - this->parentIntersectNode->myRoads.begin());
        if (idx < 0 || idx >= (int) this->parentIntersectNode->roadIdx.size()) {
            std::cerr << "Abort! Abort! Something drastically wrong happened!";
            return;
        }
        this->indexOfRoadInIntersectNode.push_back(idx);
    }
}

void TrafficNode::Update() {
    int counter = 0;
    for (auto& road: this->myRoad) {
        //get displacement until 
        int displacement = this->parentIntersectNode->displacements[this->indexOfRoadInIntersectNode[counter]];

        //check if this road is allowed in this phase
        bool allowed = this->allowedToProceed[counter];

        //find the car farthest before the intersection + a safety length + half the car's length (cause im stupid)
        float stopPos = displacement + CarInfo::safetyUntilTrafficStop + CarInfo::carHalfLength;
        auto farthest = road->getFarthestCarBeforeDisplace(stopPos);

        //allow/disallow to continue based on if road is closed due to traffic light(s) or not
        if (farthest.first != nullptr) {
            Car* car = farthest.first;
            
            //push in the car + length left of that car until the stop light
            if (allowed) {
                road->allowedCarsAtTraffic.push(std::pair<Car*, float>(car, std::max((float) 0, stopPos - farthest.second)));
            } else {
                road->blockedCarsAtTraffic.push(std::pair<Car*, float>(car, std::max((float) 0, stopPos - farthest.second)));
            }
        }
    }
}