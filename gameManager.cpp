#include "gameManager.h"

sf::Vector2f GameManager::convertWorldToScreen(sf::Vector2f world) {
    return sf::Vector2f(world.x, -world.y);
}

sf::Vector2f GameManager::convertScreenToWorld(sf::Vector2f screen) {
    return sf::Vector2f(screen.x, -screen.y);
}