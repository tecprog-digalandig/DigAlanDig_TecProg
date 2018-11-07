#include "MiniTileMap.h"
#include <algorithm>
#include "Alan.h"
#include "Camera.h"
#include "Common.h"
#include "Game.h"

MiniTileMap::MiniTileMap(GameObject &associated, TileSet *tile_set,
                         TileMap *tileMap, std::weak_ptr<GameObject> alan)
    : Component(associated), tile_map(tile_map), tile_set(tile_set), alan(alan) {}

MiniTileMap::~MiniTileMap() {}

/*
    Renderiza as camadas do mapa.
*/
void MiniTileMap::render(Common::Layer layer) const {
    if (!alan.lock()) return;

    int y_min;
    int x = associated.box.x;
    int y = associated.box.y;
    int val_pos;

    Vec2 alan_pos = alan.lock()->getGridPosition();

    y_min = alan_pos.y - 5;

    // Camera::pos.y / Game::getInstance()->getCurrentState().GetGridSize();

    for (int posY = y_min; posY < tile_map->GetHeight(); posY++)
    {
        for (int posX = 0; posX < tile_map->GetWidth(); posX++)
        {
            // Coloca a marmota no minimapa
            // val_pos = tileMap->At(posX, posY, TileMap::Layers::BLOCOS);
            if (posY < 0)
            {
                val_pos = 1;
            }
            else if (alan_pos.x == posX && alan_pos.y == posY)
            {
                val_pos = 5;
                // Faz a borda o minimapa
            } 
            else if (tile_map->At(posX, posY, TileMap::Layers::ITENS)) 
            {
                val_pos = 4;
            } 
            else if (posY >
                alan.lock()->GetComponent<Alan *>()->getMaxPosition() +
                           7) 
            {
                val_pos = 1;
            } 
            else 
            {
                val_pos = 1;
            }
            
            tile_set->RenderTile(val_pos, x, y);

            x += tile_set->GetTileWidth();
        }
        x = associated.box.x;
        y += tile_set->GetTileHeight();
    }
}
