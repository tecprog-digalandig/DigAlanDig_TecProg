#include "TileSet.h"
#include "Common.h"
#include "Game.h"

TileSet::TileSet(const std::string& file) {
    json j;
    Common::read_Json(j, file);

    std::string imgFile = j.at("image");
    imgFile.replace(imgFile.begin(), imgFile.begin() + 3, "assets/");
    tileSet_d = Resources::getImage(imgFile);
    imgFile.replace(imgFile.end() - 4, imgFile.end() - 4, "_light");
    tileSet_l = Resources::getImage(imgFile);
    SDL_SetTextureBlendMode(tileSet_l.get(), SDL_BLENDMODE_ADD);
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
        item2type[4] = item2type[5] = (int)Common::ItemType::gold;
    item2type[11] = item2type[16] = item2type[17] = item2type[20] =
        item2type[21] = item2type[8] = (int)Common::ItemType::diamond;
    item2type[6] = item2type[7] = item2type[18] = item2type[19] =
        item2type[14] = item2type[15] = (int)Common::ItemType::petroleum;
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

    SDL_RenderCopy(Game::getInstance()->GetRenderer(), tile_set, &clip, &pos);
}
