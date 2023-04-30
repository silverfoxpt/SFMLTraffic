#include "drawbezier.h"

void DrawBezier::Input(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            //check if node in box
            if (!this->parent->checkInMapFromActualPos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                return;
            }

            //create node
            SaveNode newNode = this->parent->getSaveNodeFromMousePos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));

            //check if first time
            if (!this->clickedFirst && (!this->clickedSecond)) {
                this->clickedFirst = true;
                this->firstNode = newNode;
            } 

            else if (this->clickedFirst && (!this->clickedSecond)) {
                sf::Vector2f firstPos = this->firstNode.mapPos;
                sf::Vector2f secondPos(event.mouseButton.x, event.mouseButton.y);

                //create a quadratic bezier curve (for now, should upgrade to )
            }
        }
    }
}