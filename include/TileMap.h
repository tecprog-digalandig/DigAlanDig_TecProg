#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
  public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet)
        : Component(associated), tileSet(tileSet) {
        Load(file);
    }
    ~TileMap();

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet) { this->tileSet = tileSet; }
    int At(int x, int y, int z = 0) { return tileMatrix[z][x][y]; }

    void Update(float dt) {}
    void Render();
    bool Is(std::string type) { return !type.compare("TileMap"); }

    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth() { return width; }
    int GeHeight() { return height; }
    int GetDepth() { return depth; }

  private:
    int*** tileMatrix;
    TileSet* tileSet;
    int width, height, depth;
};

#endif  // TILEMAP_H
