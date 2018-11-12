#include "EnemySpawn.h"
#include "Camera.h"
#include "Enemy.h"
#include "Game.h"

<<<<<<< HEAD
void EnemySpawn::Update(float dt)
{
    while ( current_y < ( (int)( ( (Camera::pos.y + Camera::screenSize.y) /
            Game::getInstance()->getCurrentState().GetGridSize() ) + 4) ) )
    {
        for (int x = 0; x < tileMap->GetWidth(); ++x)
        {
            if (int enemy = tileMap->At(x, current_y, TileMap::Layers::INIMIGOS) )
            {
=======
void EnemySpawn::update(float dt) {
    while (currentY <
           ((int)(((Camera::pos.y + Camera::screenSize.y) /
                   Game::GetInstance()->GetCurrentState().GetGridSize()) +
                  4))) {
        for (int x = 0; x < tileMap->GetWidth(); x++) {
            if (int enemy =
                    tileMap->At(x, currentY, TileMap::Layers::INIMIGOS)) {
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
                GameObject* go = new GameObject();
                go->box.x =
                    x * Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2;
                go->box.y =
                    current_y *
                        Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2;
                go->gridPosition.x = x;
                go->gridPosition.y = current_y;
                go->addComponent(new Enemy(*go, enemy));
                Game::getInstance()->getGridControl()->AddEnemy(go);
                Game::getInstance()->getCurrentState().AddObject(go);
            }
        }
        ++current_y;
    }
}
