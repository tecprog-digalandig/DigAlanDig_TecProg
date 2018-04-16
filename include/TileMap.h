#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
  public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
        : Component(associated), tileSet(tileSet) {
        Load(file);
    }
    ~TileMap();

    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet) { this->tileSet = tileSet; }
    int At(int x, int y, int z = 0) const { return tileMatrix[z][x][y]; }

    void Update(float dt) {}
    void Render() const;
    bool Is(const std::string& type) const { return !type.compare("TileMap"); }

    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0) const;

    int GetWidth() const { return width; }
    int GeHeight() const { return height; }
    int GetDepth() const { return depth; }

  private:
    int*** tileMatrix;
    TileSet* tileSet;
    int width, height, depth;
};

#endif  // TILEMAP_H
