#include "trafficmap.h"

#include "../IMGui Stuffs/imgui.h"
#include "../IMGui Stuffs/imgui-SFML.h"

TrafficMap::TrafficMap(sf::RenderWindow* rend) {
    this->myRend = rend;
}

void TrafficMap::Initialize(Map* map, IntersectMap* intersectMap) {
    this->parent = map;
    this->intersectMap = intersectMap;
}

void TrafficMap::Update() {
    
}

void TrafficMap::Input(sf::Event event) {
    if (this->intersectMap->intersectionStatus == 1) { //traffic node mode  
        int idx = 0;
        for (auto& shape: this->intersectMap->shapes) {
            if (shape.isMouseOver(*this->myRend)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                    this->showWindow = true;
                    this->intersectIdx = idx;
                }
            }
            idx++;
        }
    }
}

void TrafficMap::Visualize(sf::Event event) {
    if (!this->showWindow) {return;}

    //get position of intersection node
    auto pos = this->intersectMap->circles[this->intersectIdx].getPosition();
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));

    //open the modal popup to configure the traffic node
    ImGui::OpenPopup("Add traffic participants");
    if (ImGui::BeginPopupModal("Add traffic participants", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        //important stuff here
        //imgui for choosing roads
        std::vector<std::string> up;
        for (int i = 0; i < this->parent->intersections[intersectIdx].intersectingRoadIndex.size(); i++) {
            std::string tmp = "Road " + std::to_string(i);
            up.push_back(tmp);
        }
        
        std::vector<const char*> upChar;
        upChar.reserve(up.size());
        for (const auto& str : up) {
            upChar.push_back(str.c_str());
        }
        ImGui::SetNextItemWidth(150); 
        ImGui::Combo("##roadchoose", this->getChoosenRoadIdx(), upChar.data(), upChar.size()); 

        //close button
        ImGui::Separator();
        if (ImGui::Button("Close", ImVec2(120, 0))) { 
            this->showWindow = false; 
            this->intersectIdx = -1;
            ImGui::CloseCurrentPopup(); 
        }

        ImGui::EndPopup();
    }
}

