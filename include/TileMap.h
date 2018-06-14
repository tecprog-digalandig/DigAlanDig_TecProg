#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>
#include <unordered_map>
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
  public:
    TileMap(GameObject& associated, const std::string& file,
            bool infinity = false);
    ~TileMap();

    void Load(const std::string& file);
    void LoadList(const std::string& file);
    void SetTileSet(TileSet* tileSet) { this->tileSet = tileSet; }
    int At(int x, int y, int z = 1);

    void Update(float dt) {}
    void RhythmUpdate() {}
    void Render(Common::Layer layer) const;

    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0) const;

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetDepth() const { return depth; }

    void GetDamageGround(int damage, Vec2 posDamage);
    int GetNextFile();

  private:
    std::vector<std::vector<int>> tileMat;
    std::vector<std::string> TileMapsFiles;
    std::unordered_map<std::string, int> layerIndex;
    TileSet* tileSet;
    int width = 0, height = 0, depth = 0;
    const int groundLayer = 1;
    bool infinity;
};

#endif  // TILEMAP_H
