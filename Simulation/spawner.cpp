#include "spawner.h"

Spawner::Spawner() {
    this->currentNumOfCar = 0;
}

void Spawner::Initialize(Tilemap* tilemap) {
    this->tilemap = tilemap; 

    //find all spawnable roads
    for (auto &row: this->tilemap->tilemap) {
        for (auto &tile: row) {
            for (int i = 0; i < (int) tile.roads.size(); i++) {
                Road* road = tile.getRoad(i);

                if (road->inputRoads.empty()) {
                    this->startableRoads.push_back(road);
                }
            }
        }
    }

    //create all da default cars
    for (int i = 0; i < GameManager::totalNumOfCar; i++) {
        //hard coded
        Car newCar(5, CarInfo::carLength);
        newCar.SetColor(sf::Color::Red);

        this->cars.push_back(newCar);
        this->carActive.push_back(false);
    }
}

void Spawner::Update() {
    if (this->currentNumOfCar >= GameManager::totalNumOfCar) {
        return;
    }

    //find spawnable road that are not OCCUPIED
    std::vector<Road*> unoccupiedRoads;
    for (auto road: this->startableRoads) {
        if (!road->inputJammed) {
            unoccupiedRoads.push_back(road);
        }
    }

    //shuffle da list
    int left = GameManager::totalNumOfCar - this->currentNumOfCar;
    Randomize::rand.shuffle_list(unoccupiedRoads);

    //not done
    for (int i = 0; i < std::max(left, (int) unoccupiedRoads.size()); i++) {
        
    }
}

void Spawner::HardReset() {
    this->startableRoads.clear();
    this->cars.clear();

    this->currentNumOfCar = 0;
}

Car* Spawner::getCar(int idx) {
    if (idx < 0 || idx >= (int) this->cars.size()) {std::cout << "Error: Car not found!" << '\n'; return nullptr;}

    return &this->cars[idx];
}