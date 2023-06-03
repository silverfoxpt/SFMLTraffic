#ifndef H_NODES
#define H_NODES

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../json.hpp"
using json = nlohmann::json;

class SaveNode {
    public:
        sf::Vector2f relativePos;
        sf::Vector2f mapPos;

        SaveNode() {}

        json getJson() {
            json j;
            j["relativePos"] = {relativePos.x, relativePos.y};
            j["mapPos"] = {mapPos.x, mapPos.y};
            return j;
        }

        SaveNode(json j) {
            this->relativePos = sf::Vector2f(j["relativePos"][0], j["relativePos"][1]);
            this->mapPos = sf::Vector2f(j["mapPos"][0], j["mapPos"][1]);
        }
};

class SaveRoad {
    public:
        std::vector<SaveNode> nodes;

        SaveRoad() {}

        json getJson() {
            json j;
            std::vector<json> tmp;
            for (SaveNode node: this->nodes) {
                tmp.push_back(node.getJson());
            }
            j["nodes"] = tmp;
            return j;
        }

        SaveRoad(json j) {
            std::vector<json> tmp = j["nodes"];
            for (json j2: tmp) {
                nodes.push_back(SaveNode(j2));
            }
        }
};

class SaveIntersectingNode {
    public:
        SaveNode posNode;
        std::vector<int> intersectingRoadIndex;
        std::vector<int> startNodeIdx;

        json getJson() {
            json j;
            j["posNode"] = posNode.getJson();
            j["intersectingRoadIndex"] = intersectingRoadIndex;
            j["startNodeIdx"] = startNodeIdx;
            return j;
        }

        SaveIntersectingNode(json j) {
            this->posNode = j["posNode"];
            this->intersectingRoadIndex = j["intersectingRoadIndex"].get<std::vector<int>>();
            this->startNodeIdx = j["startNodeIdx"].get<std::vector<int>>();
        }

        SaveIntersectingNode(SaveNode pos, std::vector<int> roadIdx, std::vector<int> start) {
            this->posNode = pos;
            this->intersectingRoadIndex = roadIdx;
            this->startNodeIdx = start;
        }
};

class SaveRoadParticipantNode {
    public:
        int intersectingNodeIdx;
        int roadInIntersectionIdx;
        int phaseIdx;

        SaveRoadParticipantNode(int interNodeIdx, int roadIntersectionIdx, int phaseIdx) {
            this->intersectingNodeIdx = interNodeIdx;
            this->roadInIntersectionIdx = roadIntersectionIdx;
            this->phaseIdx = phaseIdx;
        }
};

class SaveIntraConnection {
    public:
        int inputRoadIdx;
        int outputRoadIdx;

        SaveIntraConnection() {} //default

        SaveIntraConnection(int id1, int id2) {
            this->inputRoadIdx = id1;
            this->outputRoadIdx = id2;
        }

        bool isEqual(SaveIntraConnection& other) {return (this->inputRoadIdx == other.inputRoadIdx) && (this->outputRoadIdx == other.outputRoadIdx); }

        json getJson() {
            json j;
            j["inputRoadIdx"] = inputRoadIdx;
            j["outputRoadIdx"] = outputRoadIdx;
            return j;
        }

        SaveIntraConnection(json j) {
            this->inputRoadIdx = j["inputRoadIdx"];
            this->outputRoadIdx = j["outputRoadIdx"];
        }
};

class SaveInterConnection {
    public:
        int roadIdx;
        int portIdx; //counted left to right and top to bottom
        int sideIdx; // 0 top, 1 right, 2 down, 3 left
        int inputOrOutput; // 0 for input, 1 for output

        bool isEqual(SaveInterConnection& other) {return (this->roadIdx == other.roadIdx) && (this->inputOrOutput == other.inputOrOutput); }

        json getJson() {
            json j;
            j["roadIdx"] = roadIdx;
            j["portIdx"] = portIdx;
            j["sideIdx"] = sideIdx;
            j["inputOrOutput"] = inputOrOutput;
            return j;
        }

        SaveInterConnection(json j) {
            this->roadIdx = j["roadIdx"];
            this->portIdx = j["portIdx"];
            this->sideIdx = j["sideIdx"];
            this->inputOrOutput = j["inputOrOutput"];
        }

        SaveInterConnection(int road, int port, int side, int inout) {
            this->roadIdx = road;
            this->portIdx = port;
            this->sideIdx = side;
            this->inputOrOutput = inout;
        }
};

#endif