#include <SFML/Graphics.hpp>

#include "tile.h"
#include "tilemap.h"
#include "gameManager.h"
#include "gameobject.h"

//public variables
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
Tilemap tilemap(5, 5, 100, 100, 100, 100, &window);
GameObject car(25, 50);

sf::Texture carTex;

//initialize some static vars
sf::RenderWindow* GameManager::rend = &window;
float GameManager::windowWidth = window.getSize().x;
float GameManager::windowHeight = window.getSize().y;

void Initialize() {
    car.SetColor(sf::Color::Red);
    car.SetPosition(sf::Vector2f(50, -50));

    //get some tex
    //carTex.loadFromFile("carTop.png");
    //car.SetTexture(&carTex);
}

void Test() {
    tilemap.Debug();
    //window.draw(car.user);
    //car.Rotate(-0.005);
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