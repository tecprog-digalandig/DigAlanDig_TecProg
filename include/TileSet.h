#ifndef TILESET_H
#define TILESET_H
#include <string>
#define INCLUDE_SDL
#include "SDL_include.h"

class TileSet {
  public:
    TileSet(int tileWidth, int tileHeight, std::string file);

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth() { return tileWidth; }
    int GetTileHeight() { return tileHeight; }

  private:
    SDL_Texture* tileSet;

    int rows, columns;
    int tileWidth, tileHeight;
};

#endif  // TILESET_H
