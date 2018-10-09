/**
* @file EnemySpawn.cpp
* @copyright 2018 Pedro H.
* @brief This class controls where and when the enemy will spawn, using as
* parameters the camera and players position on the screen.
*/


#include "EnemySpawn.h"
#include "Camera.h"
#include "Enemy.h"
#include "Game.h"


/**
* @brief controls the spawn of an enemy on the screen setting the poition on x
* and y axis.
* @param [in] dt is the variation of time between an input and the movement on
* the screen.
* @return void
*/

void EnemySpawn::update(float dt)
{
    while ( current_y < ( (int)( ( (Camera::pos.y + Camera::screenSize.y) /
            Game::getInstance()->getCurrentState().GetGridSize() ) + 4) ) )
    {
        for (int x = 0; x < tileMap->GetWidth(); ++x)
        {
            if (int enemy = tileMap->At(x, current_y, TileMap::Layers::INIMIGOS) )
            {
                GameObject* go = new GameObject();
                go->box.x = x * Game::getInstance()->getCurrentState().GetGridSize() -
                    Game::getInstance()->getCurrentState().GetGridSize() / 2;
                go->box.y = current_y * Game::getInstance()->getCurrentState().GetGridSize() -
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
