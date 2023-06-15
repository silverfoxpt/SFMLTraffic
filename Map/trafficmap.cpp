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

void TrafficMap::AddTrafficPhasePopup() {
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
        for (int i = 0; i < (int) this->parent->intersections[intersectIdx].intersectingRoadIndex.size(); i++) {
            std::string tmp = "Road " + std::to_string(this->choosenToActualRoadIdx(i));
            up.push_back(tmp);
        }
        
        std::vector<const char*> upChar;
        upChar.reserve(up.size());
        for (const auto& str : up) {
            upChar.push_back(str.c_str());
        }

        ImGui::Text("Add"); ImGui::SameLine();
        ImGui::SetNextItemWidth(150); 
        ImGui::Combo("##roadchoose", this->getChoosenRoadIdx(), upChar.data(), upChar.size()); 

        //imgui for choosing phase
        std::vector<std::string> up2;
        for (int i = 0; i < (int) this->parent->trafficPhases.size(); i++) {
            std::string tmp = "Phase " + std::to_string(i);
            up2.push_back(tmp);
        }

        std::vector<const char*> upChar2;
        upChar2.reserve(up2.size());
        for (const auto& str : up2) {
            upChar2.push_back(str.c_str());
        }

        ImGui::Text("to"); ImGui::SameLine();
        ImGui::SetNextItemWidth(150); 
        ImGui::Combo("##phasechoose", this->getChoosenPhaseIdx(), upChar2.data(), upChar2.size()); 

        //button to add
        if (ImGui::Button("Add##trafficphasebuttonadd")) {
            SaveRoadParticipantNode newTrafficRoad = SaveRoadParticipantNode(this->intersectIdx, this->choosenToActualRoadIdx(this->choosenRoadIdx), this->choosenPhaseIdx);
            this->parent->roadParticipants.push_back(newTrafficRoad);

            this->showWindow = false; 
            this->intersectIdx = -1;
            ImGui::CloseCurrentPopup(); 
        }

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

void TrafficMap::Visualize(sf::Event event) {
    this->AddTrafficPhasePopup();
}

int TrafficMap::choosenToActualRoadIdx(int intersectRoadIdx) {
    return this->parent->intersections[this->intersectIdx].intersectingRoadIndex[intersectRoadIdx];
}

