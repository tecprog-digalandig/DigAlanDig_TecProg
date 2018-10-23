#include "EnemySpawn.h"
#include "Camera.h"
#include "Enemy.h"
#include "Game.h"

void EnemySpawn::Update(float delta_time) {
    while (currentY <
           ((int)(((Camera::pos.y + Camera::screenSize.y) /
                   Game::getInstance()->getCurrentState().GetGridSize()) +
                  4))) {
        for (int x = 0; x < tileMap->GetWidth(); x++) {
            if (int enemy =
                    tileMap->At(x, currentY, TileMap::Layers::INIMIGOS)) {
                GameObject* go = new GameObject();
                go->box.x =
                    x * Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2;
                go->box.y =
                    currentY *
                        Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2;
                go->gridPosition.x = x;
                go->gridPosition.y = currentY;
                go->addComponent(new Enemy(*go, enemy));
                Game::getInstance()->getGridControl()->AddEnemy(go);
                Game::getInstance()->getCurrentState().AddObject(go);
            }
        }
        currentY++;
    }
}
