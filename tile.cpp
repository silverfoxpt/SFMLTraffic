#include "tile.h"

Tile::Tile(int posX, int posY, int width, int height, int tileId) {
    this->posX = posX;
    this->posY = posY;

    this->width = width;
    this->height = height;

    this->tileId = 0;
}

void Tile::Debug() {
    //draw outline
    sf::RectangleShape rect(sf::Vector2f(this->width, this->height));
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1.5);
    rect.setPosition(sf::Vector2f(this->posX, this->posY));
    this->myWindow->draw(rect);

    //draw nodes
    for (Node x : this->nodes) {
        int xPos = x.posX;
        int yPos = x.posY;

        sf::CircleShape a(6.0);
        a.setPosition(xPos, yPos);
        a.setFillColor(sf::Color::Green);

        this->myWindow->draw(a);
    }    
}