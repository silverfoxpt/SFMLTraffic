#include "trafficnode.h"

void TrafficManager::Initialize(Tilemap* tilemap, IntersectManager* intersectManager) {
    for (int i = 0 ; i < tilemap->rows; i++) {
        std::vector<TileTrafficManager> row; this->managers.push_back(row);

        for (int j = 0; j < tilemap->cols; j++) {
            TileTrafficManager newManager;
            newManager.Initialize(tilemap->GetTile(i, j), intersectManager, tilemap->tileIds[i][j]);
            this->managers[i].push_back(newManager);
        }
    }
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

        this->nodes.push_back(newTrafficNode);
    }
}

void TrafficNode::Initialize(Tile* parentTile, IntersectNode* parentIntersectNode, TileTrafficManager* parentTrafficManager) {
    this->parentTile = parentTile;
    this->parentIntersectNode = parentIntersectNode;
    this->parentTrafficManager = parentTrafficManager;
}