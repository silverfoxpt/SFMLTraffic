#include <SFML/Graphics.hpp>

#include "tile.h"
#include "tilemap.h"

sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

void Test() {
    
}

int main()
{
    Tilemap tilemap(5, 5, 100, 100, 100, 100, &window);
    
    
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
        tilemap.Debug();    

        window.display();
    }

    return 0;
}