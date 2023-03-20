#include <SFML/Graphics.hpp>

#include "tile.h"
#include "tilemap.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

void Test() {
    Tilemap tilemap(4, 4, 100, 100, 100, 100, &window);
    tilemap.Debug();
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