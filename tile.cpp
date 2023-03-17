#include "tile.h"

Tile::Tile(int posX, int posY, int width, int height, int tileId) {
    this->posX = posX;
    this->posY = posY;

    this->width = width;
    this->height = height;

    this->tileId = tileId;

    //set up nodes
    std::vector<std::pair<float, float>> setup = TileInfo::nodePosMapper[this->tileId];
    for (int i = 0 ; i < (int) setup.size(); i++) {
        Node newNode(setup[i]); 
        newNode.setPosFromParentPos(this->posX, this->posY, this->width, this->height);

        this->nodes.push_back(newNode);
    }

    //setup connections
    this->connections = TileInfo::nodeConnectionMapper[this->tileId];
}

void Tile::Debug() {
    //draw outline
    sf::RectangleShape rect(sf::Vector2f(this->width, this->height));
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1.5);
    rect.setPosition(sf::Vector2f(this->posX, this->posY));
    this->myWindow->draw(rect);

    std::vector<sf::CircleShape> a;
    for (int i = 0; i < (int) this->nodes.size(); i++) {
        a.push_back(sf::CircleShape(5.0));
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
    }    
}

Node::Node(std::pair<float, float> rel) {
    this->relativePos = rel;
}

void Node::setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    this->posX = parentPosX + parentWidth * this->relativePos.first;
    this->posY = parentPosY + parentHeight * this->relativePos.second;
}