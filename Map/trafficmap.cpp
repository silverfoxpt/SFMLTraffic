#include "trafficmap.h"

void TrafficMap::Initialize(Map* map, IntersectMap* intersectMap) {
    this->parent = map;
    this->intersectMap = intersectMap;
}