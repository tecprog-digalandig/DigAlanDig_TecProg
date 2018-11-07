#include "Sprite.h"
#include "Alan.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

void Sprite::Open(const std::string &file) {
    texture = Resources::getImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    width /= frameCount;
    frameTimeTotal = frameTime;
    setFrame(0);
    associated.box.size.Set(width, height);
    timeElapsed = 0;
}

void Sprite::Open(SpriteState sstate, int dir) {
    texture = Resources::getImage(sstate.file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    width /= sstate.totalFrameCount;
    frameCount = sstate.frameCount;
    initFrame = dir * sstate.frameCount;

    setFrame(initFrame);
    frameTimeTotal = sstate.frameTime * sstate.frameCount;
    frameTime = sstate.frameTime;
    associated.box.size.Set(width, height);
    timeElapsed = 0;
}

void Sprite::SetScaleX(double scaleX, double scaleY) {
    scale.x = scaleX ? scaleX : scale.x;
    scale.y = scaleY ? scaleY : scale.y;
}

void Sprite::setFrame(int frame) {
    currentFrame = frame;
    Vec2 size(width, height);
    Vec2 pos(width * (currentFrame), 0);
    clipRect = Rect(pos, size);
}

void Sprite::render(Common::Layer layer) const {
    if (isOpen()) {
        Vec2 offset;
        if (associated.world_reference) offset = Camera::pos;
        Rect dst(associated.box.pos - offset, {(double)width, (double)height});

        if (scale.x != 1 || scale.y != 1) dst.Scale(scale);

        SDL_Rect dstRect = dst;
        SDL_RenderCopyEx(Game::getInstance()->GetRenderer(), texture.get(),
                         &clipRect, &dstRect, associated.angleDeg, nullptr,
                         SDL_FLIP_NONE);
    }
}

void Sprite::Update(float delta_time) {
    timeElapsed += delta_time;

    selfDestructCount.Update(delta_time);
    if (secondsToSelfDestruct > 0 &&
        selfDestructCount.get() > secondsToSelfDestruct) {
        associated.RequestDelete();
        return;
    }

    if (associated.GetComponent<Alan *>() != nullptr) {
        AlanUpdate(delta_time);
        return;
    } else {
        if (frameTime > 0 && ((currentFrame + 1) * frameTime <= timeElapsed)) {
            int newFrame = floor(timeElapsed / frameTime);
            setFrame(newFrame % frameCount);
        }
    }
}

void Sprite::AlanUpdate(float delta_time) {
    if (frameTime > 0) {
        if (timeElapsed - (frameTime * (currentFrame - initFrame)) >=
            frameTime) {
            if ((currentFrame - initFrame) < (frameCount - 1)) {
                setFrame(currentFrame + 1);

            } else {
                setFrame(initFrame);
            }
        }
    } else if (frameTime != -1) {
        if (timeElapsed - (std::abs(frameTime) * (currentFrame - initFrame)) >=
            std::abs(frameTime)) {
            if ((currentFrame - initFrame) < (frameCount - 1))
                setFrame(currentFrame + 1);
        }
    }
}
