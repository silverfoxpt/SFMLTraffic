#include "tile.h"

Tile::Tile(int posX, int posY, int width, int height, int tileId, Tilemap* parentTile) {
    this->posX = posX;
    this->posY = posY;

    this->width = width;
    this->height = height;

    this->tileId = tileId;
    this->parentTilemap = parentTile;

    //set up road
    this->roads = TileInfo::roadInTileMap[this->tileId];
    std::vector<RoadInfo> info = TileInfo::roadInterConnection[this->tileId];
    
    for (int i = 0; i < (int) this->roads.size(); i++) {
        RoadInfo c = info[i];
        //set up size
        this->roads[i].setAllPosOfNodeFromParentPos(
            this->parentTilemap->xPos, this->parentTilemap->yPos,
            this->parentTilemap->tileWidth, this->parentTilemap->tileHeight
        );
    }
}

void Tile::Debug() { //not important, so I won't be refactoring any time soon
    //draw outline
    sf::RectangleShape rect(sf::Vector2f(this->width, this->height));
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1);
    rect.setPosition(sf::Vector2f(this->posX, this->posY));
    this->myWindow->draw(rect);

    /*std::vector<sf::CircleShape> a;
    for (int i = 0; i < (int) this->nodes.size(); i++) {
        a.push_back(sf::CircleShape(5.0));
    }

    //draw connections
    for (int u = 0; u < (int) this->nodes.size(); u++) {
        for (int v : this->neighbor[u]) {
            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(this->nodes[u].posX, this->nodes[u].posY), sf::Color::Yellow),
                sf::Vertex(sf::Vector2f(this->nodes[v].posX, this->nodes[v].posY), sf::Color::Cyan)
            };
            this->myWindow->draw(line , 2, sf::Lines);
        }
    }

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

void Tile::SetUpConnection() {
    
}

Node::Node(std::pair<float, float> rel) {
    this->relativePos = rel;
}

void Node::setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    this->posX = parentPosX + parentWidth * this->relativePos.first;
    this->posY = parentPosY + parentHeight * this->relativePos.second;
}


void Road::setInputRoad(std::shared_ptr<Road> road) {
    this->inputRoad = road;
}

void Road::setOutputRoad(std::shared_ptr<Road> road) {
    this->outputRoad = road;
}

void Road::setAllPosOfNodeFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    for (int i = 0; i < (int) this->nodes.size(); i++) {
        this->nodes[i].setPosFromParentPos(parentPosX, parentPosY, parentWidth, parentHeight);
    }
}

Road::Road(std::vector<Node> nodes) {
    this->nodes = nodes;
}