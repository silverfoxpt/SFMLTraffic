#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <fstream>

#include "Map/map.h"

#include "Simulation/tile.h"
#include "Simulation/tilemap.h"
#include "Simulation/car.h"
#include "Simulation/carInfo.h"
#include "Simulation/randomsfml.h"
#include "Simulation/intersectnode.h"

#include "IMGui Stuffs/imgui.h"
#include "IMGui Stuffs/imgui-SFML.h"

#include "drawshapes.h"

#include "json.hpp"

// for convenience
using json = nlohmann::json;

//really early stuff initialization
Rand Randomize::rand;
std::vector<IntersectNode> IntersectManager::intersections;

//public variables
sf::RenderWindow    window(sf::VideoMode(800, 800), "Traffic Simulation 2D");
sf::RenderWindow    mapmaker(sf::VideoMode(900, 700), "Map 2D");

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;
float GameManager::deltaTime = 1/60.0;
int GameManager::tileSize = 100;

Tilemap             tilemap(5, 7, 50, 50, GameManager::tileSize, GameManager::tileSize, &window);

MapInterConnect     editorInterconnectMap(&mapmaker);
MapIntraConnect     editorIntraconnectMap(&mapmaker);
IntersectMap        editorIntersectMap(&mapmaker);
DrawBezier          editorDrawBezier(&mapmaker);
Drawmap             editorDrawmap(&mapmaker);
Map                 editor(&mapmaker);
    
//test variables
std::vector<Car>    cars;
int                 c = 0;
sf::Clock           testClock;

sf::Texture         carTex;

void Initialize() {
    editorIntersectMap.Initialize(&editor);
    editorDrawmap.Initialize(&editor);
    editorDrawBezier.Initialize(&editor);
    editorIntraconnectMap.Initialize(&editor);
    editorInterconnectMap.Initialize(&editor);
    editor.Initialize(&editorDrawmap, &editorDrawBezier, &editorIntersectMap, &editorIntraconnectMap, &editorInterconnectMap);

    window.setPosition(sf::Vector2i(50, 50));
    mapmaker.setPosition(sf::Vector2i(870, 50));

    //test
    testClock.restart();
    for (int i = 0; i < 30; i++) {
        Car newCar(5, CarInfo::carLength);
        newCar.SetColor(sf::Color::Red);

        cars.push_back(newCar);
    }
}

void Test() {
    tilemap.Debug();
    tilemap.Update();
     
    //moreeeeeeeeeee testssssssssss
    int counter = 0;
    Tile* tile = tilemap.GetTile(0, 0);

    for (auto &car: cars) {
        window.draw(car.user);

        if (testClock.getElapsedTime().asSeconds() >= 0.2 && c == counter) {
            if (c % 2 == 0 && !tile->roads[0].inputJammed) {
                tile->roads[0].acceptCar(&car);
                testClock.restart();
                c++;
            } else if (c % 2 == 1 && !tile->roads[1].inputJammed) {
                tile->roads[1].acceptCar(&car);
                testClock.restart();
                c++;
            }
        }
        counter++;
    }
}

void SFMLRoad() {
    ImGui::Begin("Road status##Default");

    ImGui::BeginChild("ScrollingRegion2", ImVec2(0, 100), true, ImGuiWindowFlags_HorizontalScrollbar);
    int delRoad = -1;
    for (int i = 0; i < (int) editor.roads.size(); i++) {
        std::string info = "Road " + std::to_string(i);

        if (ImGui::Selectable(info.c_str(), false, ImGuiSelectableFlags_None, ImVec2(0, 0))) {
            //delete road
            delRoad = i;
        }

        if (ImGui::IsItemHovered()) {
            editor.infoVisualizeRoad(i, sf::Color::Yellow);
            ImGui::SetTooltip("Click to delete road");
        }
    }
    ImGui::EndChild();

    ImGui::End();

    if (delRoad != -1) {
        editor.deleteRoad(delRoad);
    }
}

void SFMLConnection() {
    //new board for connection status
    ImGui::Begin("Connection status##Default");
    ImGui::Spacing();
    
    //intra road connection
    ImGui::Text("Intra-connection");

    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 100), true, ImGuiWindowFlags_HorizontalScrollbar);
    int counter = 0;
    std::vector<int> delIntra;
    for (auto& intraConnect: editor.intraConnections) {
        std::string info = "" + std::to_string(intraConnect.inputRoadIdx) + " -> " + std::to_string(intraConnect.outputRoadIdx);

        //clicked on 
        ImGui::Selectable(info.c_str(), false, ImGuiSelectableFlags_None, ImVec2(0, 0));

        if (ImGui::IsItemHovered()) {
            editorIntraconnectMap.VisualizeSelectedRoad(counter);
            if (ImGui::IsMouseClicked(0)) { // check for left click=
                auto connect = editor.getIntraConnection(counter);
                editorIntraconnectMap.MergeRoad(connect->inputRoadIdx, connect->outputRoadIdx);
            }
            else if (ImGui::IsMouseClicked(1)) { // check for right click=
                delIntra.push_back(counter);
            }

            ImGui::SetTooltip("Left click to merge roads, right click to delete");
        }
        counter++;
    }
    for (int x: delIntra) {editor.intraConnections.erase(editor.intraConnections.begin() + x);}
    ImGui::EndChild();

    //inter road connection
    ImGui::Text("Inter-connection");

    ImGui::BeginChild("InterScroll", ImVec2(0, 100), true, ImGuiWindowFlags_HorizontalScrollbar);
    counter = 0;
    const char* sides[] = { "top", "right", "down", "left" };
    std::vector<int> delInter;
    for (auto& interConnect: editor.interConnections) {
        std::string info = "Road " + std::to_string(interConnect.roadIdx) + " -> port " + std::to_string(interConnect.portIdx) + ", " + sides[interConnect.sideIdx] + " side as " + 
            (interConnect.inputOrOutput == 0 ? "input" : "output");

        //clicked on 
        ImGui::Selectable(info.c_str(), false, ImGuiSelectableFlags_None, ImVec2(0, 0));

        if (ImGui::IsItemHovered()) {
            editorInterconnectMap.VisualizeSelectedRoad(counter);
            if (ImGui::IsMouseClicked(0)) { // check for left click
                editorInterconnectMap.MergeRoad(counter);
            }
            else if (ImGui::IsMouseClicked(1)) { // check for right click
                delInter.push_back(counter);
            }
            ImGui::SetTooltip("Left click to warp road to port, right click to delete");
        }
        counter++;
    }
    for (int x: delInter) {editor.interConnections.erase(editor.interConnections.begin() + x);}
    ImGui::EndChild();

    ImGui::End();
}

void SFMLInterConnectPort() {
    int side = *editorInterconnectMap.getConnectSide();
    int port = *editorInterconnectMap.getConnectPort();

    sf::Vector2f pos;
    int additional = (float) editor.size / (editor.numGrid + 1);

    switch(side) {
        case 0: {
            pos = sf::Vector2f(editor.offset.x + port * additional, editor.offset.y); 
            DrawUtils::drawCircle(&mapmaker, sf::Vector2f(pos.x, pos.y - 10), 3.5, sf::Color::Yellow);
            break;
        } 
        case 1: {
            pos = sf::Vector2f(editor.offset.x + editor.size, editor.offset.y + port * additional); 
            DrawUtils::drawCircle(&mapmaker, sf::Vector2f(pos.x + 10, pos.y), 3.5, sf::Color::Yellow);
            break;
        }
        case 2: {
            pos = sf::Vector2f(editor.offset.x + port * additional, editor.offset.y + editor.size); 
            DrawUtils::drawCircle(&mapmaker, sf::Vector2f(pos.x, pos.y + 10), 3.5, sf::Color::Yellow);
            break;
        }
        case 3: {
            pos = sf::Vector2f(editor.offset.x, editor.offset.y + port * additional); 
            DrawUtils::drawCircle(&mapmaker, sf::Vector2f(pos.x - 10, pos.y), 3.5, sf::Color::Yellow);
            break;
        }
    }
}

void SFMLHandleJson() {
    // Read from file
    std::ifstream roadInFile("road.json");
    if (!roadInFile) {
        std::cerr << "Failed to open road.json" << std::endl;
        return;
    }
    json parsed;
    try {
        parsed = json::parse(roadInFile);
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse road.json: " << e.what() << std::endl;
        return;
    }
    roadInFile.close();

    std::vector<json> tiles;
    try {
        tiles = parsed.get<std::vector<json>>();
    } catch (const std::exception& e) {
        std::cerr << "Failed to extract vector from road.json: " << e.what() << std::endl;
        return;
    }

    // Write to file
    json tile = editor.getFullJson(); 
    tiles.push_back(tile);
    json newFile = tiles; 
    std::ofstream roadOutFile("road.json");
    if (!roadOutFile) {
        std::cerr << "Failed to open road.json for writing" << std::endl;
        return;
    }
    roadOutFile << newFile.dump(4);
    roadOutFile.close();
}

void SFMLAction() {
    ImGui::Begin("Action##Default");
    if (ImGui::Button("Save tile to map##act1")) {
        SFMLHandleJson();
    }
    //ImGui::SameLine();
    if (ImGui::Button("Clear tile##act2")) {

    }
    ImGui::End();
}

void SFMLUpdate() {
    ImGui::Begin("Map editor##Default");
    ImGui::InputInt("Status", editor.getStatus());

    //intersection mode
    if (*editor.getStatus() == 2) {
        ImGui::InputInt("Intersection status", editorIntersectMap.getStatus());
    }

    //connection mode
    if (*editor.getStatus() == 3) {
        ImGui::Spacing();
        ImGui::Text("Intra-connection");
        ImGui::Text("Connect"); ImGui::SameLine();
        ImGui::SetNextItemWidth(150); ImGui::InputInt("##intraconnect1", editorIntraconnectMap.getConnect1()); ImGui::SameLine();
        ImGui::Text("to"); ImGui::SameLine();
        ImGui::SetNextItemWidth(150); ImGui::InputInt("##intraconnect2", editorIntraconnectMap.getConnect2());
        if (ImGui::Button("Connect")) {
            editorIntraconnectMap.Submit();
        }

        ImGui::Spacing();
        ImGui::Text("Inter-connection");
        ImGui::Text("Connect"); ImGui::SameLine();
        ImGui::SetNextItemWidth(150); ImGui::InputInt("##interconnectroad", editorInterconnectMap.getRoadId()); ImGui::SameLine();
        
        ImGui::Text("at side"); ImGui::SameLine();
        const char* sides[] = { "Top", "Right", "Down", "Left" };
        ImGui::SetNextItemWidth(100); ImGui::Combo("##interconnectside", editorInterconnectMap.getConnectSide(), sides, IM_ARRAYSIZE(sides)); ImGui::SameLine();

        ImGui::Text(", port"); ImGui::SameLine();
        ImGui::SetNextItemWidth(200); ImGui::SliderInt("##interconnectport", editorInterconnectMap.getConnectPort(), editorInterconnectMap.minPort, editorInterconnectMap.maxPort); 
        if (ImGui::IsItemHovered()) {
            SFMLInterConnectPort();
        }
        ImGui::SameLine();

        ImGui::Text("as"); ImGui::SameLine();
        const char* inout[] = { "Input", "Output"};
        ImGui::SetNextItemWidth(100); ImGui::Combo("##interconnectinout", editorInterconnectMap.getInputOrOutput(), inout, IM_ARRAYSIZE(inout)); 
        if (ImGui::Button("Connect##intercon2")) {
            editorInterconnectMap.Submit();
        }
    }

    ImGui::End();

    SFMLConnection();
    SFMLRoad();
    SFMLAction();
}

void InitTest() {
    json j;
    j["name"] = "Hung";
    j["mapPos"] = {0.1, 0.2};
    std::string jdump = j.dump();
    std::cout << jdump << '\n';

    float x = j["mapPos"][0], y = j["mapPos"][1];
    std::cout << x << " " << y << '\n';
}

int main()
{
    //ImGui::LoadIniSettingsFromDisk("imgui.ini");
    ImGui::SFML::Init(mapmaker);
    ImGui::SetCurrentContext(ImGui::CreateContext());

    //ImGui::LoadIniSettingsFromDisk("window.ini");
    //ImGui::SFML::Init(window);
    //ImGui::SetCurrentContext(ImGui::CreateContext());
    Initialize();
    //InitTest();

    sf::Clock deltaTime;
    sf::Clock deltaTime2;
    while (window.isOpen() && mapmaker.isOpen())
    {   
        //normal window
        sf::Event event;
        while (window.pollEvent(event))
        {
            //ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //ImGui::SFML::Update(window, deltaTime.restart());
        //ImGui::SetCurrentContext(ImGui::GetCurrentContext());
        window.clear();        
        
        Test(); 

        //ImGui::SFML::Render(window);
        

        //mapmaker
        //sf::Event mapEvent;
        while(mapmaker.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(mapmaker, event);
            editor.Input(event);

            if (event.type == sf::Event::Closed)
                mapmaker.close();
        }
        ImGui::SFML::Update(mapmaker, deltaTime2.restart());
        ImGui::SetCurrentContext(ImGui::GetCurrentContext());
        mapmaker.clear(sf::Color(60, 60, 60, 255));

        editor.Update();
        editor.Visualize(event);
        SFMLUpdate();
        editor.LateUpdate();

        ImGui::SFML::Render(mapmaker);

        window.display();
        mapmaker.display();

        //std::cout << 1.0 / deltaTime.getElapsedTime().asSeconds() << '\n';
    }
    ImGui::SFML::Shutdown();
    return 0;
}