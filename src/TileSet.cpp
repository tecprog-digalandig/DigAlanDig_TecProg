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

    tileHeight = j.at("tileheight");
    tileWidth = j.at("tilewidth");

    int width, height;
    SDL_QueryTexture(tile_set, nullptr, nullptr, &width, &height);
    columns = width / tileWidth;
    rows = height / tileHeight;

    if (width != j.at("imagewidth") || height != j.at("imageheight")) {
        std::cout << "Tileset mismatch" << std::endl;
        exit(EXIT_SUCCESS);
    }

    item2type[12] = item2type[13] = item2type[22] = item2type[23] =
        item2type[4] = item2type[5] = (int)Common::ItemType::gold;
    item2type[11] = item2type[16] = item2type[17] = item2type[20] =
        item2type[21] = item2type[8] = (int)Common::ItemType::diamond;
    item2type[6] = item2type[7] = item2type[18] = item2type[19] =
        item2type[14] = item2type[15] = (int)Common::ItemType::petroleum;
}

void TileSet::RenderTile(unsigned index, float x, float y) const {
    if (index == 0) return;
    /*Tiled index starts at 1*/
    index--;
    if ((int)index >= (rows * columns)) {
        std::cerr << "Tile is out of range" << std::endl;
        exit(EXIT_SUCCESS);
    }

    SDL_Rect pos = {(int)x, (int)y, tileWidth, tileHeight};
    SDL_Rect clip = {tileWidth * ((int)index % columns),
                     tileHeight * ((int)index / columns), tileWidth,
                     tileHeight};

    SDL_RenderCopy(Game::getInstance()->GetRenderer(), tile_set, &clip, &pos);
}
