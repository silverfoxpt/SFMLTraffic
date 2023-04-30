#include "drawmap.h"

Drawmap::Drawmap() {  //default constructor
     
}

Drawmap::Drawmap(sf::RenderWindow* rend) {
    this->myRend = rend;
}

void Drawmap::Initialize(Map* map) {
    this->parent = map;
}

void Drawmap::Input(sf::Event event) {
    //still drawing, add node if mouse pressed & in map
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (!this->parent->checkInMapFromActualPos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                return;
            }
            
            SaveNode newNode = this->parent->getSaveNodeFromMousePos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            nodes.push_back(newNode);
        }
    }

    //stop the drawing, add to main map
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (!this->nodes.empty()) { //not empty
                SaveRoad newRoad;
                newRoad.nodes = this->nodes; this->nodes.clear();

                this->parent->addRoad(newRoad);
            }
        }
    }
}

void Drawmap::Visualize(sf::Event event) {
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

        //draw lines between last node and mouse if mouse in map
        sf::Vector2i p = sf::Mouse::getPosition(*this->myRend);
        sf::Vector2f pos(p.x, p.y);

        if (!this->parent->checkInMapFromActualPos(pos)) {
            return;
        }

        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(this->nodes[this->nodes.size() - 1].mapPos.x, this->nodes[this->nodes.size() - 1].mapPos.y), sf::Color::Red),
            sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::Red)
        };
        this->myRend->draw(line , 2, sf::Lines);
    }
}