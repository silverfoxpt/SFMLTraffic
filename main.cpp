#include <SFML/Graphics.hpp>

#include "tile.h"
#include "tilemap.h"
#include "car.h"
#include "carInfo.h"
#include "randomsfml.h"

//really early stuff
Rand Randomize::rand;

//public variables
sf::RenderWindow window(sf::VideoMode(800, 800), "Traffic Simulation 2D");
Tilemap tilemap(5, 7, 50, 50, 100, 100, &window);

std::vector<Car> cars;
int c = 0;
sf::Clock testClock;

sf::Texture carTex;

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;
float GameManager::deltaTime = 1/300.0;

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

        if (testClock.getElapsedTime().asSeconds() >= c * 0.2 && c == counter) {
            if (c % 2 == 0 && !tile->roads[0].inputJammed) {
                tile->roads[0].acceptCar(&car);
                c++;
            } else if (!tile->roads[1].inputJammed) {
                tile->roads[1].acceptCar(&car);
                c++;
            }
            
        }
        counter++;
    }
}

int main()
{
    Initialize();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        Test(); 

        window.display();
    }

    return 0;
}