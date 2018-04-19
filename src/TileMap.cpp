#include "TileMap.h"
#include <fstream>
#include <iostream>
#include "Camera.h"

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

inline int inRange(int value, int min, int max) {
    return (value < min) ? min : ((value > max) ? max : value);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) const {
    int w = tileSet->GetTileWidth();
    int h = tileSet->GetTileHeight();

    // Optimization, for only drawing what is on screen
    int cinit = cameraX / w;
    int cmax = cinit + ceil(Camera::screenSize.x / (double)w) + 1;
    cinit = inRange(cinit, 0, width);
    cmax = inRange(cmax, 0, width);

    int linit = cameraY / h;
    int lmax = linit + ceil(Camera::screenSize.y / (double)h) + 1;
    linit = inRange(linit, 0, height);
    lmax = inRange(lmax, 0, height);

    for (int line = linit; line < lmax; ++line)
        for (int col = cinit; col < cmax; ++col)
            tileSet->RenderTile(tileMatrix[layer][line][col], col * w - cameraX,
                                line * h - cameraY);
}

void TileMap::Render() const {
    for (int i = 0; i < depth; ++i)
        RenderLayer(i, Camera::pos.x * (i + 1), Camera::pos.y * (i + 1));
}
