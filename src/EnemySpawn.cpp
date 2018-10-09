#include "EnemySpawn.h"
#include "Camera.h"
#include "Enemy.h"
#include "Game.h"

void EnemySpawn::Update(float dt)
{
    while ( current_y < ( (int)( ( (Camera::pos.y + Camera::screenSize.y) /
            Game::GetInstance()->GetCurrentState().GetGridSize() ) + 4) ) )
    {
        for (int x = 0; x < tileMap->GetWidth(); ++x)
        {
            if (int enemy = tileMap->At(x, current_y, TileMap::Layers::INIMIGOS) )
            {
                GameObject* go = new GameObject();
                go->box.x =
                    x * Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize() / 2;
                go->box.y =
                    current_y * Game::GetInstance()->GetCurrentState().GetGridSize() -
                    Game::GetInstance()->GetCurrentState().GetGridSize() / 2;
                go->gridPosition.x = x;
                go->gridPosition.y = current_y;
                go->AddComponent(new Enemy(*go, enemy));
                Game::GetInstance()->GetGridControl()->AddEnemy(go);
                Game::GetInstance()->GetCurrentState().AddObject(go);
            }
        }
        ++current_y;
    }
}
