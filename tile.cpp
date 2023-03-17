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
    std::vector<std::pair<int, int>> tmp = TileInfo::nodeConnectionMapper[this->tileId];
    for (int i = 0; i < (int) tmp.size(); i++) {
        int u = tmp[i].first;
        int v = tmp[i].second;

        if (this->neighbor.find(u) == this->neighbor.end()) {
            std::vector<int> a; 
            a.push_back(v);
            this->neighbor[u] = a;
        } else {
            this->neighbor[u].push_back(v);
        }
    }
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
    }   
}

Node::Node(std::pair<float, float> rel) {
    this->relativePos = rel;
}

void Node::setPosFromParentPos(int parentPosX, int parentPosY, int parentWidth, int parentHeight) {
    this->posX = parentPosX + parentWidth * this->relativePos.first;
    this->posY = parentPosY + parentHeight * this->relativePos.second;
}