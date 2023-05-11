#include "tile.h"

Tile::Tile(int posX, int posY, int width, int height, int tileId, Tilemap* parentTile, int rowIdx, int colIdx) {
    this->posX = posX;
    this->posY = posY;

    this->width = width;
    this->height = height;

    this->tileId = tileId;
    this->parentTilemap = parentTile;

    this->rowIdx = rowIdx;
    this->colIdx = colIdx;

    //set up road
    this->roads = TileInfo::roadInTileMap[this->tileId];

    for (int i = 0; i < (int) this->roads.size(); i++) {
        //set up size
        this->roads[i].setAllPosOfNodeFromParentPos(
            this->posX, this->posY,
            this->parentTilemap->tileWidth, this->parentTilemap->tileHeight
        );
        
        //calculate length
        this->roads[i].CalculateRoadLength();

        //set up idx for debug
        this->roads[i].colIdx = this->colIdx;
        this->roads[i].rowIdx = this->rowIdx;
    }

    //set up road intersection
    /*sf::Vector2i nullRoad(-99999, -99999);
    std::vector<std::pair<int, int>> roadIntraCon = TileInfo::roadIntraConnection[this->tileId];

    for (int i = 0; i < (int) this->roads.size() - 1; i++) {
        Road* first = &this->roads[i];
        for (int j = i+1; j < (int) this->roads.size(); j++) {
            Road* second = &this->roads[j];

            //check if two roads are already pushing into each other (in roadIntraConection)
            bool already = false;
            for (auto x : roadIntraCon) {
                //if (this->tileId == 3) {std::cout << i << " " << j << '\n';}
                if (x.first == i && x.second == j) {already = true; break;}
                if (x.first == j && x.second == i) {already = true; break;}
            }
            if (already) {continue;}

            //find all the nodes
            std::vector<std::pair<std::pair<int, int>, sf::Vector2i>> addIntersectNode;

            for (int a = 0; a < (int) first->nodes.size()-1; a++) {
                Node a1 = first->nodes[a], a2 = first->nodes[a+1];
                for (int b = 0; b < (int) second->nodes.size()-1; b++) {
                    Node b1 = second->nodes[b], b2 = second->nodes[b+1];

                    sf::Vector2i intersect = Math::Intersect(a1.getPos(), a2.getPos(), b1.getPos(), b2.getPos());
                    if (intersect == nullRoad) {
                        continue;
                    }
                    
                    //debug
                    std::cout << "Intersection found: " << rowIdx << " " << colIdx << " " << i << " " << j 
                        << " " << intersect.x << " " << intersect.y << '\n';

                    //damn future me
                    addIntersectNode.push_back(std::pair<std::pair<int, int>, sf::Vector2i>(std::pair<int, int>(a, b), intersect));
                }
            }

            //find displacement of intersection
            for (std::pair<std::pair<int, int>, sf::Vector2i> inter: addIntersectNode) {
                //first road
                float displace1 = 0;
                for (int i = 0; i < inter.first.first; i++) {
                    displace1 += Math::Length(first->nodes[i+1].getPos() - first->nodes[i].getPos());
                }
                displace1 += Math::Length(first->nodes[inter.first.first].getPos() - sf::Vector2f(inter.second.x, inter.second.y));
                
                //second road
                float displace2 = 0;
                for (int i = 0; i < inter.first.second; i++) {
                    displace2 += Math::Length(second->nodes[i+1].getPos() - second->nodes[i].getPos());
                }
                displace2 += Math::Length(second->nodes[inter.first.second].getPos() - sf::Vector2f(inter.second.x, inter.second.y));
                
                IntersectNode newIntersection(inter.second, displace1, displace2);
                IntersectManager::addNode(newIntersection);
            }
        }
    }*/
}

void Tile::Debug(int &c) { //this just draw stuffs, not important, so I won't be refactoring any time soon
    //draw outline
    sf::RectangleShape rect(sf::Vector2f(this->width, this->height));
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1);
    rect.setPosition(sf::Vector2f(this->posX, this->posY));
    this->myWindow->draw(rect);

    //draw connections
    for (int i = 0; i < (int) this->roads.size(); i++) {
        std::pair<float, float> prev(-100, -100);

        for (int j = 0; j < (int) this->roads[i].nodes.size(); j++) {
            Node tmp = this->roads[i].nodes[j];
            if (j == 0) {
                prev = std::pair<float, float>(tmp.posX, tmp.posY);
                continue;
            }

            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(prev.first, prev.second), sf::Color::Green),
                sf::Vertex(sf::Vector2f(tmp.posX, tmp.posY), sf::Color::Green)
            };
            this->myWindow->draw(line , 2, sf::Lines);

            prev = std::pair<float, float>(tmp.posX, tmp.posY);
        }
    }

    
    //draw nodes
    /*for (Road &road: this->roads) {
        for (Node x : road.nodes) {
            int xPos = x.posX;
            int yPos = x.posY;

            sf::CircleShape a(3);
            a.setOrigin(sf::Vector2f(3, 3));
            a.setPosition(xPos, yPos);
            a.setFillColor(sf::Color::Red);

            this->myWindow->draw(a);
        }
    }*/   
}

//only used in initialization, so idc if it's slow
std::vector<Road*> Tile::GetInterRoad(int side, int idx, bool isInputRoad) {
    std::vector<RoadInterInfo> info = TileInfo::roadInterConnection[this->tileId];
    std::vector<Road*> result;

    for (int i = 0; i < (int) this->roads.size(); i++) {
        //handling input
        if (isInputRoad) {
            if (info[i].inputId == idx && info[i].extraSideIn == side) { //checking
                result.push_back(&this->roads[i]);
            }
        } 
        
        //handling output
        else { 
            if (info[i].outputId == idx && info[i].extraSideOut == side) { //checking
                result.push_back(&this->roads[i]);
            }
        }
    }
    return result;
}

void Tile::SetUpRoadConnection() {
    std::vector<RoadInterInfo> info = TileInfo::roadInterConnection[this->tileId];

    //up, right, down, left
    int dx[4]           = {-1, 0, +1, 0}; 
    int dy[4]           = {0, +1, 0, -1};
    int opposite[4]     = {2, 3, 0, 1};
    
    int infoCount = 0;
    for (int i = 0; i < (int) this->roads.size(); i++) {
        RoadInterInfo c = info[infoCount];
        if (c.roadId != i) {continue;}
        infoCount++;

        //set up inputs from other tile
        if (c.inputFromOtherTile) {
            int side = c.extraSideIn;
            int connector = c.inputId;

            if (this->parentTilemap->TileExist(this->rowIdx + dx[side], this->colIdx + dy[side])) {
                Tile* myTile = this->parentTilemap->GetTile(this->rowIdx + dx[side], this->colIdx + dy[side]);

                //calculate the opposite tile side
                int sideOut = opposite[side];

                //get da road
                std::vector<Road*> myRoad = myTile->GetInterRoad(sideOut, connector, false); //search for output road
                for (Road* road: myRoad) { //the road exist
                    this->roads[i].addInputRoad(road); //which means, an OUTPUT ROAD from ANOTHER TILE is the INPUT to THIS road
                }
            }
        }
        else {
            //idc
        }

        //set up outputs from other tiles
        if (c.outputToOtherTile) {
            int side = c.extraSideOut;
            int connector = c.outputId;
            
            if (this->parentTilemap->TileExist(this->rowIdx + dx[side], this->colIdx + dy[side])) {
                Tile* myTile = this->parentTilemap->GetTile(this->rowIdx + dx[side], this->colIdx + dy[side]);
                
                //calculate the opposite tile side
                int sideOut = opposite[side];

                //get da road
                std::vector<Road*> myRoad = myTile->GetInterRoad(sideOut, connector, true); //search for input road
                for (Road* road: myRoad) { //the road exist
                    this->roads[i].addOutputRoad(road); //which means, an INPUT ROAD from ANOTHER TILE is the OUTPUT to THIS road
                }
            }
        }
        else {
            //idc
        } 
    }

    //set up road intra-connections (connections between roads in 1 tile)
    std::vector<std::pair<int, int>> info2 = TileInfo::roadIntraConnection[this->tileId];
    for (std::pair<int, int> p: info2) {
        this->roads[p.first].addOutputRoad(&this->roads[p.second]);
        this->roads[p.second].addInputRoad(&this->roads[p.first]);
    } 
}

void Tile::Update() {
    for (Road &road: this->roads) {
        road.Update();
    }
}


Node::Node(std::pair<float, float> rel) {
    this->relativePos = rel;
}

Node::Node(sf::Vector2i actualPos) {
    this->posX = actualPos.x;
    this->posY = actualPos.y;
}

void Node::setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    this->posX = parentPosX + parentWidth * this->relativePos.first;
    this->posY = parentPosY + parentHeight * this->relativePos.second;
}

void Node::Update() {

}

sf::Vector2f Node::getPos() {
    return sf::Vector2f(this->posX, this->posY);
}

void Road::addNode(Node node) {
    this->nodes.push_back(node);
}

void Road::addInputRoad(Road* road) {
    this->inputRoads.push_back(road);
}

void Road::addOutputRoad(Road* road) {
    this->outputRoads.push_back(road);
}

void Road::setAllPosOfNodeFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    for (int i = 0; i < (int) this->nodes.size(); i++) {
        this->nodes[i].setPosFromParentPos(parentPosX, parentPosY, parentWidth, parentHeight);
    }
}

Road::Road(std::vector<Node> nodes) {
    this->nodes = nodes;
    this->outputBlocked = false;
    this->inputJammed = false;

    this->inputRoads.clear();
}

void Road::CalculateRoadLength() {
    //calculate road length
    this->roadLength = 0;
    int c = 0;

    sf::Vector2f prevNodePos(0, 0);
    for (Node node: this->nodes) {
        //std::cout << node.posX << " " << node.posY << '\n';
        if (c == 0) { 
            c++;
            prevNodePos = sf::Vector2f(node.posX, node.posY);
            continue;
        }
        this->roadLength += Math::Length(sf::Vector2f(node.posX, node.posY) - prevNodePos);
        prevNodePos = sf::Vector2f(node.posX, node.posY);
        c++;
    }
    //std::cout << (int) this->roadLength << '\n';
}

sf::Vector2f Road::getVectorBetweenTwoNodes(int startNodeIdx) {
    float first = this->nodes[startNodeIdx+1].posX - this->nodes[startNodeIdx].posX;
    float second = this->nodes[startNodeIdx+1].posY - this->nodes[startNodeIdx].posY;

    //sketchy
    return GameManager::convertScreenToWorld(sf::Vector2f(first, second));
}

void Road::acceptCar(Car* car) { //will need to be updated for traffic stopping
    //std::cout << this->rowIdx << " " << this->colIdx << '\n';

    this->currentCars.insert(this->currentCars.begin(), car);   
    this->carOnNode.insert(this->carOnNode.begin(), 0); 

    car->ResetCurrentDisplacement();

    car->SetWorldPosition(GameManager::convertScreenToWorld(sf::Vector2f(this->nodes[0].posX, this->nodes[0].posY)));
    //std::cout << this->nodes[0].posX << " " << this->nodes[0].posY << '\n';
    car->RotateToVector(this->getVectorBetweenTwoNodes(0));
}

void Road::removeCar() {
    this->currentCars.pop_back();
    this->carOnNode.pop_back();
}

//NEED REVISITING FOR RANDOMLY SELECTING ROAD OUTPUT LATER
void Road::updateCars() {
    int c = 0;
    for (Car* myCar: this->currentCars) {
        int nodeIdx = this->carOnNode[c];
        
        //if reached end of 2 nodes' path
        if (myCar->currentDisplacement >= Math::Length(this->getVectorBetweenTwoNodes(nodeIdx))) {
            if (nodeIdx == (int) this->nodes.size()-2) { //if reached last pair of nodes

                //no road left
                if (outputRoads.size() == 0) {
                    myCar->SetAcceleration(0);
                    myCar->SetVelocity(0);
                    break;
                }

                //input into next road, remove from this road, NEED REVISITING LATER
                std::vector<Road*> freeRoads;
                for (Road* road: this->outputRoads) {
                    if (!road->inputJammed) {
                        freeRoads.push_back(road);
                    }
                }

                if (freeRoads.size() == 0) {
                    break;
                }
                Road* randomRoad = freeRoads[Randomize::rand.RandomInt(0, freeRoads.size()-1)]; 
                randomRoad->acceptCar(myCar);

                //remove authority from this road
                this->removeCar();
                break;
            } 
            
            else { //just move it to next pairs of node
                this->carOnNode[c] = nodeIdx+1;

                myCar->ResetCurrentDisplacement();
                myCar->SetWorldPosition(GameManager::convertScreenToWorld(sf::Vector2f(this->nodes[nodeIdx+1].posX, this->nodes[nodeIdx+1].posY)));
                myCar->RotateToVector(this->getVectorBetweenTwoNodes(nodeIdx+1));
            }
        } else { //not reached end, then just keep swimmin'. This needs to be move into a CarManager in the future for Update()
            myCar->Advance();
        }
        c++;
    }
}

void Road::blockOutput() {
    if (this->currentCars.size() == 0) {return;}
    
    Car* car = this->currentCars.back();
    float lengthLeft = this->roadLength - car->getCarTop();

    //stop car
    if (lengthLeft <= CarInfo::lockStopLength) { 
        //car->acceleration = (car->velocity / CarInfo::desiredVelocity) * (-CarInfo::comfortDecel);
        //car->acceleration = -CarInfo::comfortDecel;

        if (lengthLeft <= 0.00001) { return; } //no devide by 0   
        car->acceleration = (-car->velocity * car->velocity) / (2 * (lengthLeft));
    }

    //slow car
    else if (lengthLeft <= CarInfo::lockSlowdownLength) {
        car->velocity = car->velocity * CarInfo::slowDownFactor;
    }
}

//probably finished
void Road::CheckIfOutputBlocked() {
    if (this->outputRoads.size() == 0) {
        this->outputBlocked = true;
        this->blockOutput();
        return;
    }

    //check if all output roads' inputs are jammed
    for (Road* road: this->outputRoads) {
        if (!road->inputJammed) {
            this->outputBlocked = false;
            
            //accelerate top car
            if (currentCars.size() > 0) {
                Car* car = this->currentCars.back();
                car->SetAcceleration(CarInfo::maxAccel);
            }

            return;
        }
    }

    this->outputBlocked = true;
    this->blockOutput();
}

//probably finished
void Road::CheckIfInputJammed() {   
    if (currentCars.size() == 0) { this->inputJammed = false; return;}

    Car* bottomCar = this->currentCars[0];
    if (bottomCar->getCarBottom() <= CarInfo::safetyInputJammedRoad) 
    {
        this->inputJammed = true;
    } 
    else 
    {
        this->inputJammed = false;
    }
}

//probably finished
void Road::UpdateCarVelocity() {
    for (int i = this->currentCars.size() - 1; i >= 1; i--) {
        //std::cout << "WTF?";

        Car* ahead = this->currentCars[i];
        Car* behind = this->currentCars[i-1];

        float distance = ahead->currentDisplacement - behind->currentDisplacement - CarInfo::carLength;
        float velocityDiff = behind->velocity - ahead->velocity;

        //calculate sstar
        float sstar = CarInfo::minDesiredDistance 
                        + behind->velocity * CarInfo::reactionTime
                        + (behind->velocity * velocityDiff) / 
                            (2 * std::sqrt(CarInfo::maxAccel * CarInfo::comfortDecel));

        //calculate new accel
        float newAcceleration = CarInfo::maxAccel * (
            1 - 
            std::pow(behind->velocity / CarInfo::desiredVelocity, CarInfo::accelExponent) - 
            std::pow(sstar / distance, 2)
        );

        //update
        behind->SetAcceleration(newAcceleration);
    }
}

void Road::Update() {
    for (Node &node: this->nodes) {
        node.Update();
    }

    this->updateCars();
    this->UpdateCarVelocity();
    this->CheckIfOutputBlocked();
    this->CheckIfInputJammed();
}   