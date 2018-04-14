#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

void Sprite::Open(std::string file) {
    if (texture) SDL_DestroyTexture(texture);

    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
    associated.box.Set(0, 0, width, height);
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
