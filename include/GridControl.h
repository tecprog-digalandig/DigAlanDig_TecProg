#ifndef GRIDCONTROL_H
#define GRIDCONTROL_H

#include <iostream>
#include <string>
#include <vector>
#include "Component.h"
#include "TileMap.h"
#include "Vec2.h"

class GridControl {
  public:
    static GridControl *getInstance();

    void SetAlan(std::weak_ptr<GameObject> alan) { this->alan = alan; }
    void SetTileMap(TileMap *tileMap) { this->tileMap = tileMap; }

    int testPath(Vec2 target, bool isAlan);

    std::weak_ptr<GameObject> GetAlan() { return alan; }

    bool VerifyEnemy(Vec2 target);

    void AddEnemy(GameObject *enemy) { enemies.emplace_back(enemy); }
    void DeleteEnemy(GameObject *enemy) {
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy),
                      enemies.end());
    }
    void ClearEnemyVector() { enemies.clear(); }

    bool WillDestroyBlock() { return (blockLife == 3); }

    int isItem(Vec2 target) {
        return tileMap->At(target.x, target.y, TileMap::Layers::ITENS);
    }

    void CheckEnemyAlanCollision(bool isAlan);

    enum WhatsThere { NONE = 0, FREE, FREE_FALL, ENEMY, ALAN, ROCK };

  private:
    std::weak_ptr<GameObject> alan;
    std::vector<GameObject *> enemies;
    TileMap *tileMap;
    static GridControl *_instance;

    int blockLife;
    int itemType;

    GridControl() {}
};
#endif  // GRIDCONTROL_H