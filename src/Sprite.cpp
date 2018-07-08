#include "Sprite.h"
#include "Alan.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

void Sprite::Open(const std::string &file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    width /= frameCount;
    frameTimeTotal = frameTime;
    SetFrame(0);
    associated.box.size.Set(width, height);
    timeElapsed = 0;
}

void Sprite::Open(SpriteState sstate, int dir) {
    texture = Resources::GetImage(sstate.file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    width /= sstate.totalFrameCount;
    frameCount = sstate.frameCount;
    initFrame = dir * sstate.frameCount;

    SetFrame(initFrame);
    frameTimeTotal = sstate.frameTime * sstate.frameCount;
    frameTime = sstate.frameTime;
    associated.box.size.Set(width, height);
    timeElapsed = 0;
}

void Sprite::SetScaleX(double scaleX, double scaleY) {
    scale.x = scaleX ? scaleX : scale.x;
    scale.y = scaleY ? scaleY : scale.y;
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    Vec2 size(width, height);
    Vec2 pos(width * (currentFrame), 0);
    clipRect = Rect(pos, size);
}

void Sprite::Render(Common::Layer layer) const {
    if (IsOpen()) {
        Vec2 offset;
        if (associated.worldReference) offset = Camera::pos;
        Rect dst(associated.box.pos - offset, {(double)width, (double)height});

        if (scale.x != 1 || scale.y != 1) dst.Scale(scale);

        SDL_Rect dstRect = dst;
        SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture.get(),
                         &clipRect, &dstRect, associated.angleDeg, nullptr,
                         SDL_FLIP_NONE);
    }
}

void Sprite::Update(float dt) {
    timeElapsed += dt;

    selfDestructCount.Update(dt);
    if (secondsToSelfDestruct > 0 &&
        selfDestructCount.Get() > secondsToSelfDestruct) {
        associated.RequestDelete();
        return;
    }

    if (associated.GetComponent<Alan *>() != nullptr) {
        AlanUpdate(dt);
        return;
    } else {
        if (frameTime > 0 && ((currentFrame + 1) * frameTime <= timeElapsed)) {
            int newFrame = floor(timeElapsed / frameTime);
            SetFrame(newFrame % frameCount);
        }
    }
}

void Sprite::AlanUpdate(float dt) {
    if (frameTime > 0) {
        if (timeElapsed - (frameTime * (currentFrame - initFrame)) >=
            frameTime) {
            if ((currentFrame - initFrame) < (frameCount - 1)) {
                SetFrame(currentFrame + 1);

            } else {
                SetFrame(initFrame);
            }
        }
    } else if (frameTime != -1) {
        if (timeElapsed - (std::abs(frameTime) * (currentFrame - initFrame)) >=
            std::abs(frameTime)) {
            if ((currentFrame - initFrame) < (frameCount - 1))
                SetFrame(currentFrame + 1);
        }
    }
}
