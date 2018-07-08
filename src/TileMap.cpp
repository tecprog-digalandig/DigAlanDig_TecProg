#include "TileMap.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include "Camera.h"
#include "Common.h"
#include "Game.h"
#include "Sprite.h"

using json = nlohmann::json;

TileMap::TileMap(GameObject& associated, const std::string& file, bool infinity)
    : Component(associated), infinity(infinity) {
    layerIndex["base"] = Layers::BASE;
    layerIndex["blocos"] = Layers::BLOCOS;
    layerIndex["itens"] = Layers::ITENS;
    layerIndex["inimigos"] = Layers::INIMIGOS;
    tileMat.resize(layerIndex.size());

    if (infinity)
        LoadList(file);
    else
        Load(file);
}
TileMap::~TileMap() {}

void TileMap::LoadList(const std::string& file) {
    json j;
    Common::read_Json(j, file);
    for (auto it = j["files"].begin(); it != j["files"].end(); ++it) {
        TileMapsFiles.push_back("assets/map/" +
                                it.value().at("name").get<std::string>());
    }

    Load(TileMapsFiles[GetNextFile()]);
}

void TileMap::Load(const std::string& file) {
    json j;
    Common::read_Json(j, file);

    std::string tileSetFile = j.at("tilesets").at(0).at("source");
    // tileSetFile.replace(tileSetFile.end() - 3, tileSetFile.end(), "json");
    tileSet = new TileSet("assets/map/" + tileSetFile);

    width = j.at("width");
    height += (int)j.at("height");
    std::cout << "height: " << height << std::endl;
    depth = j.at("layers").size();

    for (int i = 0; i < depth; i++) {
        int layer = layerIndex.at(j.at("layers").at(i).at("name"));
        std::vector<int> newdata = j.at("layers").at(i).at("data");
        tileMat[layer].insert(tileMat[layer].end(), newdata.begin(),
                              newdata.end());
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
            tileSet->RenderTile(tileMat[layer][line * width + col],
                                col * w - cameraX, line * h - cameraY);
}

int TileMap::GetNextFile() {
    static int a = -1;
    a++;
    return a % TileMapsFiles.size();
}

int TileMap::At(int x, int y, int z) {
    bool valid = (x >= 0) && (x < width) && (y >= 0) && (z >= 0) && (z < depth);
    if (!valid) return 1;

    while (infinity &&
           ((y >= height) ||
            ((Camera::pos.y + Camera::screenSize.y) / 100) >= height)) {
        Load(TileMapsFiles[GetNextFile()]);
    }

    return tileMat[z][y * width + x];
}

void TileMap::Render(Common::Layer layer) const {
    if (layer == Common::Layer::DEFAULT)
        tileSet->setTileSetDefault();
    else
        tileSet->setTileSetLight();

    for (int i = 1; i < depth - 1; ++i)
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
}

void SpawnDust(Vec2 pos) {
    GameObject* go = new GameObject();
    go->AddComponent(new Sprite(*go, "assets/img/dust.png", 3, 0.2, 3 * 0.2));
    go->box.SetCenter((pos * 100) + Vec2(50, 50));
    Game::GetInstance()->GetCurrentState().AddObject(go);
}

void TileMap::GetDamageGround(int damage, Vec2 posDamage) {
    int valPos = At(posDamage.x, posDamage.y);
    if (valPos == 1) return;

    if (--tileMat[groundLayer][(int)(posDamage.y * width + posDamage.x)] <= 2) {
        tileMat[groundLayer][(int)(posDamage.y * width + posDamage.x)] = 0;
        SpawnDust(posDamage);
    }
    // tileSet->RenderTile(valPos - 1, posDamage.x, posDamage.y);
}
