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
    ImGui::SetNextWindowFocus();

    ImGui::OpenPopup("My Popup");
    if (ImGui::BeginPopupModal("My Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!");
        
        ImGui::Separator();
        if (ImGui::Button("Close", ImVec2(120, 0))) { 
            this->showWindow = false; 
            this->intersectIdx = -1;
            ImGui::CloseCurrentPopup(); 
        }

        ImGui::EndPopup();
    }
}

