#include "drawmap.h"

Drawmap::Drawmap(sf::RenderWindow* rend, Map* par) {
    this->parent = par;

    this->myRend = rend;
}

void Drawmap::Input(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f relativePos((event.mouseButton.x - this->parent->offset.x) / GameManager::tileSize, (event.mouseButton.y - this->parent->offset.y) / GameManager::tileSize);
            sf::Vector2f actualPos(event.mouseButton.x, event.mouseButton.y);

            SaveNode newNode;
            newNode.mapPos = actualPos;
            newNode.relativePos = relativePos;

            nodes.push_back(newNode);
        }
    }
}

void Drawmap::Visualize() {
    if (!this->nodes.empty()) {
        //draw lines between all the nodes
        for (int i = 0; i < (int) this->nodes.size()-1; i++) {
            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(this->nodes[i].mapPos.x, this->nodes[i].mapPos.y), sf::Color::Red),
                sf::Vertex(sf::Vector2f(this->nodes[i+1].mapPos.x, this->nodes[i+1].mapPos.y), sf::Color::Red)
            };
            this->myRend->draw(line , 2, sf::Lines);
        }
    }
}