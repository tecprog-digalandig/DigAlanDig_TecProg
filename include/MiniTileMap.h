#ifndef MINITILEMAP
#define MINITILEMAP
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <vector>
#include "Component.h"
#include "TileMap.h"
#include "TileSet.h"

class MiniTileMap : public Component
{
  public:
    MiniTileMap(GameObject &associated, TileSet *tileSet, TileMap *tileMap,
                std::weak_ptr<GameObject> alan);

    ~MiniTileMap();

    void update(float delta_time) {}
    void rhythmUpdate() {}
    void render(Common::layer layer) const;

  private:
    TileMap *tile_map;
    TileSet *tile_set;
    std::weak_ptr<GameObject> alan;
};

#endif  // MINITILEMAP
