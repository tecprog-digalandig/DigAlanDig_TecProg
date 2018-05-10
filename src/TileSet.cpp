#include "TileSet.h"
#include "Game.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileSet(nullptr), tileWidth(tileWidth), tileHeight(tileHeight) {
    tileSet = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
    if (!tileSet) {
        std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    int width, height;
    SDL_QueryTexture(tileSet, nullptr, nullptr, &width, &height);
    columns = width / tileWidth;
    rows = height / tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y) const {
    if (index == 0) return;
    /*Tiled index starts at 1*/
    index--;
    if ((int)index >= (rows * columns)) {
        std::cerr << "Tile is out of range" << std::endl;
        exit(EXIT_SUCCESS);
    }

    SDL_Rect pos = {(int)x, (int)y, tileWidth, tileHeight};
    SDL_Rect clip = {tileWidth * ((int)index % columns),
                     tileHeight * ((int)index / columns), tileWidth,
                     tileHeight};

    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), tileSet, &clip, &pos);
}
