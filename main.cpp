#include <SFML/Graphics.hpp>

#include "tile.h"
#include "tilemap.h"
#include "car.h"
#include "carInfo.h"

//public variables
sf::RenderWindow window(sf::VideoMode(800, 800), "Traffic Simulation 2D");
Tilemap tilemap(5, 7, 50, 50, 100, 100, &window);
Car car(5, CarInfo::carLength); //car length is same as height

//more testsssssssss
Car car2(5, CarInfo::carLength); //car length is same as height
Car car3(5, CarInfo::carLength); //car length is same as height
Car car4(5, CarInfo::carLength); //car length is same as height

int c = 0;
sf::Clock testClock;

sf::Texture carTex;

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;
float GameManager::deltaTime = 1/300.0;

void Initialize() {
    car.SetColor(sf::Color::Red);

    //get some tex
    //carTex.loadFromFile("carTop.png");
    //car.SetTexture(&carTex);

    tilemap.GetTile(0, 0)->roads[0].acceptCar(&car);
    testClock.restart();
}

void Test() {
    tilemap.Debug();
    tilemap.Update();
     

    window.draw(car.user);

    //moreeeeeeeeeee testssssssssss
    window.draw(car2.user);
    window.draw(car3.user);
    window.draw(car4.user);

    if (testClock.getElapsedTime().asSeconds() >= 2 && c == 0) {
        tilemap.GetTile(0, 0)->roads[0].acceptCar(&car2);
        c = 1; 
    }
    if (testClock.getElapsedTime().asSeconds() >= 4 && c == 1) {
        tilemap.GetTile(0, 0)->roads[0].acceptCar(&car3);
        c = 2; 
    }
    if (testClock.getElapsedTime().asSeconds() >= 6 && c == 2) {
        tilemap.GetTile(0, 0)->roads[0].acceptCar(&car4);
        c = 3; 
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