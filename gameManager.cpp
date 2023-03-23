#include "gameManager.h"

void GameManager::Initialize(sf::RenderWindow *render) {
    rend = render;
    windowWidth = rend->getSize().x;
    windowHeight = rend->getSize().y;
}

sf::Vector2f GameManager::convertWorldToScreen(sf::Vector2f world) {
    return sf::Vector2f(world.x, -world.y);
}

sf::Vector2f GameManager::convertScreenToWorld(sf::Vector2f screen) {
    return sf::Vector2f(screen.x, -screen.y);
}