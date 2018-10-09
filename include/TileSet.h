#ifndef TILESET_H
#define TILESET_H
#include <memory>
#include <unordered_map>
#include "Common.h"
#define INCLUDE_SDL
#include "SDL_include.h"

using namespace std;

class TileSet {
  public:
    explicit TileSet(const string& file);

    void RenderTile(unsigned index, float x, float y) const;
    int GetTileWidth() const { return tile_width; }
    int GetTileHeight() const { return tile_height; }

    void setTileSetDefault() { tile_set = tile_set_d.get(); }
    void setTileSetLight() { tile_set = tile_set_l.get(); }

    int GetItemType(int i) {
        i--;
        auto got = item2type.find(i);
        if (got == item2type.end()) return 0;

        return item2type[i];
    }

  private:
    SDL_Texture* tile_set = nullptr;
    shared_ptr<SDL_Texture> tile_set_d = nullptr;
    shared_ptr<SDL_Texture> tile_set_l = nullptr;

    unordered_map<int, int> item2type;
    int rows = 0, columns = 0;
    int tile_width = 100, tile_height = 100;
};

#endif  // TILESET_H
