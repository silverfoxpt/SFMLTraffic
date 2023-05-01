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

                //create a quadratic bezier curve's single definiting point (for now, should upgrade to cubic later)
                this->bezierConfigure1 = sf::CircleShape(6);
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
                //check if not dragging node 1
                if (!isDraggingNode1) {
                    sf::FloatRect bound1 = this->bezierConfigure1.getGlobalBounds();

                    //get mouse pos
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->myRend);
                    sf::Vector2f p(mousePos.x, mousePos.y);

                    if (bound1.contains(p)) { //check if really clicking on node 1
                        this->isDraggingNode1 = true;
                    }
                }
            }   
        }
    }

    //stop dragging
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            this->isDraggingNode1 = false;
        }
    }

    //stop drawing and input to main map
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {

        }
    }

    //now drag stuffs
    if (this->isDraggingNode1) {
        //get mouse pos
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->myRend);
        sf::Vector2f p(mousePos.x, mousePos.y);

        this->bezierConfigure1.setPosition(p);
    }
}

void DrawBezier::Visualize(sf::Event event) {
    if (this->clickedFirst && this->clickedSecond) {
        this->myRend->draw(this->bezierConfigure1);
    }
}

void DrawBezier::Initialize(Map* myMap) {
    this->parent = myMap;
}