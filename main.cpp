#include <SFML/Graphics.hpp>

#include "tile.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

void Test() {
    Tile tile(100, 100, 100, 100, 1);
    tile.myWindow = &window;
    tile.Debug();    
}

int main()
{
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