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
            this->parentTilemap->xPos, this->parentTilemap->yPos,
            this->parentTilemap->tileWidth, this->parentTilemap->tileHeight
        );
    }
}


void Tile::Debug() { //this just draw stuffs, not important, so I won't be refactoring any time soon
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
        for (int j = 0; j < (int) this->roads[i].nodes.size(); i++) {
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

    /*
    //draw nodes
    int c = 0;
    for (Node x : this->nodes) {
        int xPos = x.posX;
        int yPos = x.posY;

        a[c].setOrigin(sf::Vector2f(5, 5));
        a[c].setPosition(xPos, yPos);
        a[c].setFillColor(sf::Color::Green);

        this->myWindow->draw(a[c]);
        c++;
    }   */
}

//only used in initialization, so idc if it's slow
Road* Tile::GetRoad(int side, int idx, bool isInputRoad) {
    std::vector<RoadInfo> info = TileInfo::roadInterConnection[this->tileId];

    for (int i = 0; i < (int) this->roads.size(); i++) {
        //handling input
        if (isInputRoad) {
            if (info[i].inputId == idx && info[i].extraSideIn == side) { //checking
                return &this->roads[i];
                //return nullptr;
            }
        } else { //handling output
            if (info[i].outputId == idx && info[i].extraSideOut == side) { //checking
                return &this->roads[i];
                //return nullptr;
            }
        }
    }
    return nullptr;
}

void Tile::SetUpRoadConnection() {
    std::vector<RoadInfo> info = TileInfo::roadInterConnection[this->tileId];

    //up, right, down, left
    int dx[4]           = {-1, 0, +1, 0}; 
    int dy[4]           = {0, +1, 0, -1};
    int opposite[4]     = {2, 3, 0, 1};

    for (int i = 0; i < (int) this->roads.size(); i++) {
        RoadInfo c = info[i];

        //set up inputs 
        if (c.inputFromOtherTile) {
            int side = c.extraSideIn;
            int connector = c.inputId;

            if (this->parentTilemap->TileExist(this->rowIdx + dx[side], this->colIdx + dy[side])) {
                Tile* myTile = this->parentTilemap->GetTile(this->rowIdx + dx[side], this->colIdx + dy[side]);

                //calculate the opposite tile side
                int sideOut = opposite[side];

                //get da road
                Road* myRoad = myTile->GetRoad(sideOut, connector, false); //search for output road
                if (myRoad != nullptr) { //the road exist
                    this->roads[i].addInputRoad(myRoad); //which means, an OUTPUT ROAD from ANOTHER TILE is the INPUT to THIS road
                }
            }
        }
        else {
            //int side = -1; //same tile
            int connector = c.inputId;
            
            //calculate the opposite tile side
            int sideOut = -1; //same tile

            //get da road
            Road* myRoad = this->GetRoad(sideOut, connector, false); //search for output road
            if (myRoad != nullptr) { //the road exist
                this->roads[i].addInputRoad(myRoad); //which means, an OUTPUT ROAD from THIS TILE is the INPUT to THIS road
            }
        }

        //set up outputs.
        if (c.outputToOtherTile) {
            int side = c.extraSideOut;
            int connector = c.outputId;
            
            if (this->parentTilemap->TileExist(this->rowIdx + dx[side], this->colIdx + dy[side])) {
                Tile* myTile = this->parentTilemap->GetTile(this->rowIdx + dx[side], this->colIdx + dy[side]);
                
                //calculate the opposite tile side
                int sideOut = opposite[side];

                //get da road
                Road* myRoad = myTile->GetRoad(sideOut, connector, true); //search for input road
                if (myRoad != nullptr) { //the road exist
                    this->roads[i].addOutputRoad(myRoad); //which means, an INPUT ROAD from ANOTHER TILE is the OUTPUT to THIS road
                }
            }
        }
        else {
            // int side = -1; //same tile
            int connector = c.inputId;
            
            //calculate the opposite tile side
            int sideOut = -1; //same tile

            //get da road
            Road* myRoad = this->GetRoad(sideOut, connector, true); //search for input road
            if (myRoad != nullptr) { //the road exist
                this->roads[i].addOutputRoad(myRoad); //which means, an INPUT ROAD from THIS TILE is the OUTPUT to THIS road
            }
        }
    }
}

Node::Node(std::pair<float, float> rel) {
    this->relativePos = rel;
}

void Node::setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    this->posX = parentPosX + parentWidth * this->relativePos.first;
    this->posY = parentPosY + parentHeight * this->relativePos.second;
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

    this->inputRoads.clear();
}