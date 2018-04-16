#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

void Sprite::Open(const std::string &file) {
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

void Sprite::Render() const {
    if (IsOpen()) {
        SDL_Rect dstRect = {(int)associated.box.x, (int)associated.box.y,
                            (int)associated.box.w, (int)associated.box.h};
        SDL_RenderCopy(Game::getInstance()->getRenderer(), texture, &clipRect,
                       &dstRect);
    }
}
