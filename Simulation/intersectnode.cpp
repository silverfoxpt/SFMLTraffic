#include "intersectnode.h"

void IntersectNode::PopulateIntersectNode() {
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
}