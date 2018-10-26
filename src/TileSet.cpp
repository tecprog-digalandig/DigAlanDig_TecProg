#include "TileSet.h"
#include "Common.h"
#include "Game.h"

TileSet::TileSet(const string& file) 
{ 
    json json_file; 
    Common::readJson(json_file, file);

    string image_file = json_file.at("image");
    image_file.replace(image_file.begin(), image_file.begin() + 3, "assets/");  
    tile_set_d = Resources::GetImage(image_file);
    image_file.replace(image_file.end() - 4, image_file.end() - 4, "_light");   
    tile_set_l = Resources::GetImage(image_file);
    SDL_SetTextureBlendMode(tile_set_l.get(), SDL_BLENDMODE_ADD);
    setTileSetDefault();

    tile_height = json_file.at("tileheight");   
    tile_width = json_file.at("tilewidth");     

    int width=0, height=0;
    SDL_QueryTexture(tile_set, nullptr, nullptr, &width, &height);
    columns = width / tile_width;
    rows = height / tile_height;

    if (width != json_file.at("imagewidth") || height != json_file.at("imageheight")) 
    { 
        cout << "Tileset mismatch" << endl;
        exit(EXIT_SUCCESS);
    }

    item2type[12] = item2type[13] = item2type[22] = item2type[23] =
        item2type[4] = item2type[5] = (int)Common::ItemType::GOLD;
    item2type[11] = item2type[16] = item2type[17] = item2type[20] =
        item2type[21] = item2type[8] = (int)Common::ItemType::DIAMOND;
    item2type[6] = item2type[7] = item2type[18] = item2type[19] =
        item2type[14] = item2type[15] = (int)Common::ItemType::PETROLEUM;
}

void TileSet::RenderTile(unsigned index, float position_x, float position_y) const 
{   
    if (index == 0) return;
    /*Tiled index starts at 1*/
    index--;
    if ((int)index >= (rows * columns)) 
    {
        cerr << "Tile is out of range" << endl;
        exit(EXIT_SUCCESS);
    }

    SDL_Rect pos = {(int)position_x, (int)position_y, tile_width, tile_height}; 
    SDL_Rect clip = {tile_width * ((int)index % columns),
                     tile_height * ((int)index / columns), tile_width,
                     tile_height};

    SDL_RenderCopy(Game::GetInstance()->GetRenderer(), tile_set, &clip, &pos);
}
