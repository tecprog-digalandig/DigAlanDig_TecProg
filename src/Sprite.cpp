#include "Sprite.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

void Sprite::Open(const std::string &file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    width /= frameCount;
    SetFrame(0);
    associated.box.size.Set(width, height);
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    scale.x = scaleX ? scaleX : scale.x;
    scale.y = scaleY ? scaleY : scale.y;
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    Vec2 size(width, height);
    Vec2 pos(width * (currentFrame % frameCount), 0);
    clipRect = Rect(pos, size);
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
        SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect,
                         &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    if ((currentFrame + 1) * frameTime <= timeElapsed) {
        SetFrame(floor(timeElapsed / frameTime));
    }
}
