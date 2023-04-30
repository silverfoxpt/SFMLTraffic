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

            //check if second time
            else if (this->clickedFirst && (!this->clickedSecond)) {
                this->clickedSecond = true;
                sf::Vector2f firstPos = this->firstNode.mapPos;
                sf::Vector2f secondPos(event.mouseButton.x, event.mouseButton.y);

                this->secondNode = newNode;

                //create a quadratic bezier curve (for now, should upgrade to cubic later)
                this->bezierConfigure1 = sf::CircleShape(2);
                this->bezierConfigure1.setFillColor(sf::Color::Red);
                this->bezierConfigure1.setPosition(Math::Middlepoint(firstPos, secondPos));

                /////dont draw anything yet, just set up da nodes
                for (int i = 0; i < this->numPoints; i++) {
                    sf::Vector2f pos = Math::Lerp(firstPos, secondPos, (float) i / numPoints);

                    SaveNode nod = this->parent->getSaveNodeFromMousePos(pos);
                    this->nodes.push_back(nod);
                }
            }

            //check if all two point is active
            else if (this->clickedFirst && this->clickedSecond) {
                
            }
        }
    }
}