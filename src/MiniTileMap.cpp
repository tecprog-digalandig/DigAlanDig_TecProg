#include "MiniTileMap.h"
#include <algorithm>
#include <assert.h>
#include "Alan.h"
#include "Camera.h"
#include "Common.h"
#include "Game.h"

/**
 * @brief Construct a new Mini Tile Map:: Mini Tile Map object
 * 
 * @param associated 
 * @param tileSet 
 * @param tileMap 
 * @param alan 
 */
MiniTileMap::MiniTileMap(GameObject &associated, TileSet *tileSet,
                         TileMap *tileMap, std::weak_ptr<GameObject> alan)
    : Component(associated), tileMap(tileMap), tileSet(tileSet), alan(alan) {}


/**
 * @brief Destroy the Mini Tile Map:: Mini Tile Map object
 * 
 */
MiniTileMap::~MiniTileMap() {}


/**
 * @brief Rendering map layers
 * 
 * @param layer 
 */
void MiniTileMap::render(Common::Layer layer) const 
{
    if (!alan.lock()) return;

    int y_min;
    int x = associated.box.x;
    int y = associated.box.y;
    int val_pos;

    Vec2 alan_pos = alan.lock()->GetGridPosition();

    y_min = alan_pos.y - 5;

    for (int pos_y = y_min; pos_y < tileMap->GetHeight(); pos_y++) 
    {
        for (int pos_x = 0; pos_x < tileMap->GetWidth(); pos_x++) 
        {
            // puts caracter on minimap
            if (pos_y < 0) 
            {
                val_pos = 1;
            } 
            else if (alan_pos.x == pos_x && alan_pos.y == pos_y) 
            {
                val_pos = 5;
                // make borda of minimap
            } 
            else if (tileMap->At(pos_x, pos_y, TileMap::Layers::ITENS)) 
            {
                val_pos = 4;
            } 
            else if (pos_y >
                       alan.lock()->GetComponent<Alan *>()->GetMaxPosition() +
                           7) 
            {
                val_pos = 1;
            } 
            else 
            {
                val_pos = 1;
            }
            tileSet->RenderTile(val_pos, x, y);

            x += tileSet->GetTileWidth();
        }
        x = associated.box.x;
        y += tileSet->GetTileHeight();
    }
}
