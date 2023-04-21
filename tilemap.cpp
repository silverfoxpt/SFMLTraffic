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
    this->tileIds[0][0] = 3;

    //setup tiles
    for (int i = 0; i < this->rows; i++) {
        this->tilemap.push_back(std::vector<Tile>());

        for (int j = 0; j < this->cols; j++) {
            Tile newTile(
                this->xPos + j * tileWidth,
                this->yPos + i * tileHeight,
                this->tileWidth,
                this->tileHeight,
                this->tileIds[i][j],
                this,
                i, 
                j
            );
            newTile.myWindow = myWindow;

            this->tilemap[i].push_back(newTile);
        }
    }

    //NOTE: TILE CONNECTION SETUP ARE ONLY VIABLE AFTER ALL TILES ARE CREATED
    //AND FILLED ON TILEMAP

    /*//set up tiles input output connections
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            this->tilemap[i][j].SetUpTileInputOutputConnection();
        }
    }*/

    //setup roads connections
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            this->tilemap[i][j].SetUpRoadConnection();
        }
    }
}

void Tilemap::Debug() {
    int c = 0;
    for (int i = 0 ; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            this->tilemap[i][j].Debug(c);
        }
    }

    //test connection -> COMPLETE
    /*int a = 1, b = 0;
    while(true) {
        std::cout << a << " " << b << '\n';
        Road* myRoad = &this->tilemap[a][b].roads[0];
        if (myRoad->outputRoads.size() > 0) {
            Road* otherRoad = myRoad->outputRoads[0];
            a = otherRoad->rowIdx;
            b = otherRoad->colIdx;
        }  else {
            break;
        }
    }*/
}

bool Tilemap::TileExist(int row, int col) {
    if (row < 0 || col < 0 || row >= this->rows || col >= this->cols) {
        return false;
    }
    else {
        return true;
    }
}

Tile* Tilemap::GetTile(int row, int col) {
    if (!this->TileExist(row, col)) {
        std::cout << "ERROR: TILE DOESN'T EXIST.";
    }
    return &this->tilemap[row][col];
}

void Tilemap::Update() {
    for (auto& v: this->tilemap) {
        for (Tile& tile: v) {
            tile.Update();
        }
    }
}