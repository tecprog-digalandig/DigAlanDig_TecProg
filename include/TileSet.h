#ifndef TILESET_H
#define TILESET_H
#include <memory>
#include <unordered_map>
#include "Common.h"
#define INCLUDE_SDL
#include "SDL_include.h"

class TileSet {
  public:
    explicit TileSet(const std::string& file);

    void RenderTile(unsigned index, float x, float y) const;
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }

    void setTileSetDefault() { tile_set = tileSet_d.get(); }
    void setTileSetLight() { tile_set = tileSet_l.get(); }

    int GetItemType(int i) {
        i--;
        auto got = item2type.find(i);
        if (got == item2type.end()) return 0;

        return item2type[i];
    }

  private:
    SDL_Texture* tileSet = nullptr;
    std::shared_ptr<SDL_Texture> tileSet_d = nullptr;
    std::shared_ptr<SDL_Texture> tileSet_l = nullptr;

    std::unordered_map<int, int> item2type;
    int rows = 0, columns = 0;
    int tileWidth = 100, tileHeight = 100;
};

#endif  // TILESET_H
