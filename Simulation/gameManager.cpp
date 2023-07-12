#include "gameManager.h"

sf::Vector2u GameManager::originalResolution = sf::Vector2u(1920, 1080);

sf::Vector2f GameManager::convertWorldToScreen(sf::Vector2f world) {
    return sf::Vector2f(world.x, -world.y);
}

sf::Vector2f GameManager::convertScreenToWorld(sf::Vector2f screen) {
    return sf::Vector2f(screen.x, -screen.y);
}

void GameManager::InitializeWindowWithResolution(sf::RenderWindow* mainWindow, sf::RenderWindow* mapWindow) {
    sf::Vector2u currentResolution = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    
    // Calculate the scale factors
    float scaleX = static_cast<float>(currentResolution.x) / originalResolution.x;
    float scaleY = static_cast<float>(currentResolution.y) / originalResolution.y;
    //std::cout << scaleX << " " << scaleY << '\n';

    // Scale the main window size
    sf::Vector2u windowSize(static_cast<unsigned int>(mainWindow->getSize().x * scaleX),
                            static_cast<unsigned int>(mainWindow->getSize().y * scaleY));
    mainWindow->setSize(windowSize);

    // Scale the map window size
    windowSize = sf::Vector2u(static_cast<unsigned int>(mapWindow->getSize().x * scaleX),
                            static_cast<unsigned int>(mapWindow->getSize().y * scaleY));
    mapWindow->setSize(windowSize);
    
    //move the map window
    int posX = mainWindow->getPosition().x + mainWindow->getSize().x + 50;
    int posY = mainWindow->getPosition().y;

    mapWindow->setPosition(sf::Vector2i(posX, posY));
}