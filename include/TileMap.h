#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>
#include <unordered_map>
#include "Component.h"
#include "TileSet.h"

using namespace std;

class TileMap : public Component {
  public:
    TileMap(GameObject& associated, const string& file,
            bool infinity = false);
    ~TileMap();

    void load(const string& file);
    void loadList(const string& file);
    void letTileSet(TileSet* tileSet) { this->tile_set = tile_set; }
    int at(int x, int y, int z = 1);

    void update(float delta_time) {}
    void rhythmUpdate() {}
    void render(Common::layer layer) const;

    void renderLayer(int layer, int cameraX = 0, int cameraY = 0) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getDepth() const { return depth; }

    void getDamageGround(int damage, Vec2 posDamage);
    void clearEnemyFromMap(Vec2 enemyPos);

    void itemCollected(Vec2 target, int layer) {
        tile_mat[layer][target.y * width + target.x] = 0;
    }

    enum Layers { BASE = 0, BLOCOS, ITENS, INIMIGOS };

  private:
    vector<vector<int>> tile_mat;
    vector<string> Tile_maps_files;
    unordered_map<string, int> layer_index;
    TileSet* tile_set;
    int width = 0, height = 0, depth = 0;
    const int ground_layer = 1;
    const int enemy_layer = 3;
    bool infinity = false;
    int current_file = 0;

    void GetNextFile();
};

#endif  // TILEMAP_H
