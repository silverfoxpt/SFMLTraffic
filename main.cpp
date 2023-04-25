#include <SFML/Graphics.hpp>

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
sf::RenderWindow window(sf::VideoMode(800, 800), "Traffic Simulation 2D");
sf::RenderWindow mapmaker(sf::VideoMode(400, 400), "Map 2D");
Tilemap tilemap(5, 7, 50, 50, 100, 100, &window);

//test variables
std::vector<Car> cars;
int c = 0;
sf::Clock testClock;

sf::Texture carTex;

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;
float GameManager::deltaTime = 1/60.0;

void Initialize() {
    //get some tex
    //carTex.loadFromFile("carTop.png");
    //car.SetTexture(&carTex);

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
    ImGui::Begin("Input");
    ImGui::Text("Graph manipulation");
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
            if (event.type == sf::Event::Closed)
                mapmaker.close();
        }

        ImGui::SFML::Update(mapmaker, deltaTime.restart());
        window.clear();
        mapmaker.clear();
        
        Test(); 
        SFMLUpdate();

        ImGui::SFML::Render(mapmaker);
        window.display();
        mapmaker.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}