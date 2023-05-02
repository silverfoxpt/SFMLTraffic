#include <SFML/Graphics.hpp>

#include "Map/map.h"

#include "Simulation/tile.h"
#include "Simulation/tilemap.h"
#include "Simulation/car.h"
#include "Simulation/carInfo.h"
#include "Simulation/randomsfml.h"
#include "Simulation/intersectnode.h"

#include "IMGui Stuffs/imgui.h"
#include "IMGui Stuffs/imgui-SFML.h"

//really early stuff initialization
Rand Randomize::rand;
std::vector<IntersectNode> IntersectManager::intersections;

//public variables
sf::RenderWindow    window(sf::VideoMode(800, 800), "Traffic Simulation 2D");
sf::RenderWindow    mapmaker(sf::VideoMode(600, 600), "Map 2D");

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;
float GameManager::deltaTime = 1/60.0;
int GameManager::tileSize = 100;

Tilemap             tilemap(5, 7, 50, 50, GameManager::tileSize, GameManager::tileSize, &window);

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
    editor.Initialize(&editorDrawmap, &editorDrawBezier, &editorIntersectMap);

    window.setPosition(sf::Vector2i(150, 150));
    mapmaker.setPosition(sf::Vector2i(1000, 150));

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

void SFMLUpdate() {
    ImGui::Begin("Map editor");
    ImGui::InputInt("Draw status", editor.getStatus());
    ImGui::End();
}

int main()
{
    ImGui::SFML::Init(mapmaker);
    Initialize();

    sf::Clock deltaTime;
    while (window.isOpen() && mapmaker.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while(mapmaker.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(mapmaker, event);
            editor.Input(event);

            if (event.type == sf::Event::Closed)
                mapmaker.close();
        }

        ImGui::SFML::Update(mapmaker, deltaTime.restart());
        window.clear();
        mapmaker.clear();
        
        Test(); 
        SFMLUpdate();
        editor.Update();
        editor.Visualize(event);

        ImGui::SFML::Render(mapmaker);
        window.display();
        mapmaker.display();

        //std::cout << 1.0 / deltaTime.getElapsedTime().asSeconds() << '\n';
    }
    ImGui::SFML::Shutdown();
    return 0;
}