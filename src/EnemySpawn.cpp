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
#include <assert.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"


/**
* @brief controls the spawn of an enemy on the screen setting the poition on x
* and y axis.
* @param [in] dt is the variation of time between an input and the movement on
* the screen.
* @return void
*/

void EnemySpawn::update(float dt)
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in EnemySpawn::update");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("EnemySpawn::update accessed");

        assert(dt >= 0);
        while ( current_y < ( static_cast<int>( ( (Camera::pos.y + Camera::screenSize.y) /
                Game::getInstance()->getCurrentState().GetGridSize() ) + 4) ) )
        {
            for (int x = 0; x < tileMap->GetWidth(); x = x + 1)
            {
                assert(x>=0);
                if (int enemy = tileMap->At(x, current_y, TileMap::Layers::INIMIGOS) )
                {
                    assert(current_y >= 0);
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
                else
                {
                    //Nothing to do
                }
            }
            current_y = current_y + 1;
        }
    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}
