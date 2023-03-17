#include "tilemap.h"

Tilemap::Tilemap(int rows, int cols, int xPos, int yPos, int tileWidth, int tileHeight, sf::RenderWindow* myWindow) {
    this->rows = rows;
    this->cols = cols;

    this->xPos = xPos;
    this->yPos = yPos;

    this->tileHeight = tileHeight;
    this->tileWidth = tileWidth;

    //test, setup some tile ids
    for (int i = 0; i < this->rows; i++) {
        this->tileIds.push_back(std::vector<int>());
        for (int j = 0; j < this->cols; j++) {
            this->tileIds[i].push_back(1);
        }
    }

    //setup nodes
    for (int i = 0; i < this->rows; i++) {
        this->tilemap.push_back(std::vector<Tile>());

        for (int j = 0; j < this->cols; j++) {
            Tile newTile(
                this->xPos + i * tileWidth,
                this->yPos + j * tileHeight,
                this->tileWidth,
                this->tileHeight,
                this->tileIds[i][j]
            );
            newTile.myWindow = myWindow;

            this->tilemap[i].push_back(newTile);
        }
    }
}

void Tilemap::Debug() {
    for (int i = 0 ; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            this->tilemap[i][j].Debug();
        }
    }
}