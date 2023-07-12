#include "spawner.h"

Spawner::Spawner() {
    this->currentNumOfCar = 0;
}

void Spawner::Initialize(Tilemap* tilemap, sf::RenderWindow* window) {
    this->tilemap = tilemap; 
    this->window = window;

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
        newCar.SetWorldPosition(sf::Vector2f(0, 0));

        this->cars.push_back(newCar);
        this->carActive.push_back(false);
    }
}

void Spawner::Update() {
    if (this->currentNumOfCar >= GameManager::totalNumOfCar) {
        //visualize
        this->Visualize();
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
    Randomize::rand.shuffle_list(unoccupiedRoads);

    //find all needed unused car
    int needed = GameManager::totalNumOfCar - this->currentNumOfCar;
    int available = std::min(needed, (int) unoccupiedRoads.size());
    std::vector<Car*> availableCar;
    std::vector<int> availableCarIdx;

    for (int i = 0; i < GameManager::totalNumOfCar; i++) {
        if (!this->carActive[i]) {
            availableCar.push_back(this->getCar(i));
            availableCarIdx.push_back(i);
        }
    }

    for (int i = 0; i < available; i++) {
        //activate and use car
        this->carActive[availableCarIdx[i]] = true;
        Car* choosenCar = availableCar[i];

        unoccupiedRoads[i]->acceptCar(choosenCar);
        this->currentNumOfCar++;
    }

    //visualize
    this->Visualize();
}

void Spawner::HardReset() {
    this->startableRoads.clear();
    this->cars.clear();
    this->carActive.clear();

    this->currentNumOfCar = 0;
}

Car* Spawner::getCar(int idx) {
    if (idx < 0 || idx >= (int) this->cars.size()) {std::cout << "Error: Car not found!" << '\n'; return nullptr;}

    return &this->cars[idx];
}

void Spawner::Visualize() {
    for (int i = 0; i < GameManager::totalNumOfCar; i++) {
        if (this->carActive[i]) {
            this->window->draw(this->cars[i].user);
        }
    }
}