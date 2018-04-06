#include "Sprite.h"
#include "Game.h"

void Sprite::Open(std::string file) {
    if (texture) SDL_DestroyTexture(texture);

    texture =
        IMG_LoadTexture(Game::getInstance()->getRenderer(), file.c_str());
    if (!texture) {
        std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
    associated.box.set(0, 0, width, height);

}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    dstRect.x = associated.box.x;
    dstRect.y = associated.box.y;
    dstRect.w = associated.box.w;
    dstRect.h = associated.box.h;

    if (IsOpen())
        SDL_RenderCopy(Game::getInstance()->getRenderer(), texture, &clipRect,
                       &dstRect);
}

int Sprite::GetWidth(void) { return width; }

int Sprite::GetHeight(void) { return height; }

bool Sprite::IsOpen(void) {
    if (Sprite::texture) return true;
    return false;
}
