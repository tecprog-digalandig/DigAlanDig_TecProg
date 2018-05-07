#include "Sprite.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

void Sprite::Open(const std::string &file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
    associated.box.size.Set(width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::setScaleX(float scaleX, float scaleY) {
    scale.x = scaleX ? scaleX : scale.x;
    scale.y = scaleY ? scaleY : scale.y;
}

void Sprite::Render() const {
    if (IsOpen()) {
        Vec2 offset;
        if (associated.worldReference) offset = Camera::pos;
        Rect dst(associated.box.pos - offset, associated.box.size);

        if (scale.x != 1 || scale.y != 1) dst.Scale(scale);

        SDL_Rect dstRect = dst;
        //        SDL_RenderCopy(Game::getInstance()->getRenderer(), texture,
        //        &clipRect, &dstRect);
        SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texture, &clipRect,
                         &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}
