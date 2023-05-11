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
                this->bezierConfigure1 = sf::CircleShape(5);
                this->bezierConfigure1.setFillColor(sf::Color::Red);
                this->bezierConfigure1.setPosition(Math::Middlepoint(firstPos, secondPos));
                this->bezierConfigure1.setOrigin(sf::Vector2f(5, 5));

                /////dont draw anything yet, just set up da nodes
                for (int i = 0; i < this->numPoints; i++) {
                    sf::Vector2f pos = Math::Lerp(firstPos, secondPos, (float) i / (numPoints-1));

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
            if (!this->nodes.empty()) { //not empty
                SaveRoad newRoad;
                newRoad.nodes = this->nodes; 

                this->parent->addRoad(newRoad);
                this->nodes.clear();
            }

            this->isDraggingNode1 = false;
            this->clickedFirst = false;
            this->clickedSecond = false;
        }
    }

    //get mouse pos
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->myRend);
    sf::Vector2f interpos(mousePos.x, mousePos.y);

    //now drag stuffs and update stuffs
    if (this->isDraggingNode1) {
        this->bezierConfigure1.setPosition(interpos);
    }

    if (this->clickedFirst && this->clickedSecond) {
        //update bezier curve
        sf::Vector2f bezierConfig1 = this->bezierConfigure1.getPosition();
        sf::Vector2f anchor1 = this->firstNode.mapPos;
        sf::Vector2f anchor2 = this->secondNode.mapPos;
        for (int i = 0; i < this->numPoints; i++) {
            float t = (float) i / (this->numPoints - 1);
            sf::Vector2f p1 = Math::Lerp(anchor1, bezierConfig1, t);
            sf::Vector2f p2 = Math::Lerp(bezierConfig1, anchor2, t);
            sf::Vector2f mainPos = Math::Lerp(p1, p2, t);

            SaveNode newPoint = this->parent->getSaveNodeFromMousePos(mainPos);
            this->nodes[i] = newPoint;
        }
    }
}

void DrawBezier::Visualize(sf::Event event) {
    if (!nodes.empty()) {
        // Draw lines between all the nodes.
        for (size_t i = 0; i < nodes.size() - 1; i++) {
            sf::Vertex line[] = {
                sf::Vertex(nodes[i].mapPos, sf::Color::Red),
                sf::Vertex(nodes[i+1].mapPos, sf::Color::Red)
            };
            myRend->draw(line, 2, sf::Lines);
        }

        // Draw lines between interpos and two anchors.
        const sf::Vector2f anchor1 = firstNode.mapPos;
        const sf::Vector2f anchor2 = secondNode.mapPos;
        const sf::Vector2f interpos = bezierConfigure1.getPosition();

        // Line 1.
        sf::Vertex line1[] = {
            sf::Vertex(anchor1, sf::Color::Yellow),
            sf::Vertex(interpos, sf::Color::Yellow)
        };
        myRend->draw(line1, 2, sf::Lines);

        // Line 2.
        sf::Vertex line2[] = {
            sf::Vertex(interpos, sf::Color::Yellow),
            sf::Vertex(anchor2, sf::Color::Yellow)
        };
        myRend->draw(line2, 2, sf::Lines);
    }

    // Draw interpos point.
    if (clickedFirst && clickedSecond) {
        myRend->draw(bezierConfigure1);
    }
}

void DrawBezier::Initialize(Map* myMap) {
    this->parent = myMap;
}