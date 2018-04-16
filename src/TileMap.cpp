#include "TileMap.h"
#include <fstream>
#include <iostream>

TileMap::~TileMap() {
    for (int d = 0; d < depth; ++d) {
        for (int h = 0; h < height; ++h) {
            free(tileMatrix[d][h]);
        }
        free(tileMatrix[d]);
    }
    free(tileMatrix);
}

void TileMap::Load(const std::string &file) {
    std::ifstream input("assets/map/tileMap.txt");

    if (!input.is_open()) {
        std::cout << "Unable to open tileMap" << std::endl;
        exit(EXIT_SUCCESS);
    }

    char tmp;
    input >> width >> tmp;
    input >> height >> tmp;
    input >> depth >> tmp;

    tileMatrix = (int ***)malloc(depth * sizeof(int **));
    for (int d = 0; d < depth; ++d) {
        tileMatrix[d] = (int **)malloc(height * sizeof(int *));
        for (int h = 0; h < height; ++h) {
            tileMatrix[d][h] = (int *)malloc(width * sizeof(int));
            for (int w = 0; w < width; ++w) {
                input >> tileMatrix[d][h][w] >> tmp;
            }
        }
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) const {
    int w = tileSet->GetTileWidth();
    int h = tileSet->GetTileHeight();

    for (int line = 0; line < height; ++line)
        for (int col = 0; col < width; ++col)
            tileSet->RenderTile(tileMatrix[layer][line][col], col * w - cameraX,
                                line * h - cameraY);
}

void TileMap::Render() const {
    for (int i = 0; i < depth; ++i)
        RenderLayer(i, associated.box.x, associated.box.y);
}
