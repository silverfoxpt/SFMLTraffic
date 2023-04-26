#include "drawmap.h"

Drawmap::Drawmap(sf::RenderWindow* rend, Map* par) {
    this->isDrawing = false;
    this->parent = par;

    this->myRend = rend;
}

void Drawmap::Input(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f relativePos(event.mouseButton.x - this->parent->offset.x, 5);
        }
    }
}