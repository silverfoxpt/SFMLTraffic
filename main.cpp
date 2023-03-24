#include <SFML/Graphics.hpp>

#include "tile.h"
#include "tilemap.h"
#include "car.h"

//public variables
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
Tilemap tilemap(5, 5, 100, 100, 100, 100, &window);
Car car(25, 50);

sf::Texture carTex;

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;
float GameManager::deltaTime = 1/60.0;

void Initialize() {
    car.SetColor(sf::Color::Red);
    car.SetPosition(sf::Vector2f(100, -100));

    //get some tex
    //carTex.loadFromFile("carTop.png");
    //car.SetTexture(&carTex);
}

void Test() {
    tilemap.Debug();
    tilemap.Update();

    //window.draw(car.user);
    //car.Rotate(0.01);
    //car.Advance();
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