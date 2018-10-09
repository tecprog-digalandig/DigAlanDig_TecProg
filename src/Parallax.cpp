#include "Parallax.h"
#include "Game.h"
#include "Resources.h"

void bgCircularY::Open(const std::string &file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.size.Set(width, height);
}

void bgCircularY::render(Common::Layer layer) const {
    if (bgCircularY::texture) {
        int linit = -associated.box.y / associated.box.h;
        int lmax = linit + Camera::screenSize.y / associated.box.h;
        if (Camera::screenSize.y - associated.box.y >
            (lmax + 1) * associated.box.h)
            lmax++;

        for (int i = linit; i <= lmax; i++) {
            Rect dst(associated.box.pos.x, associated.box.pos.y + i * height,
                     (double)width, (double)height);
            SDL_Rect dstRect = dst;
            SDL_Rect clipRect = Rect(Vec2(0, 0), associated.box.size);
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture.get(),
                           &clipRect, &dstRect);
        }
    }
}

void bgCircularX::Open(const std::string &file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.size.Set(width, height);
}

void bgCircularX::render(Common::Layer layer) const {
    if (bgCircularX::texture) {
        int linit = -associated.box.x / associated.box.w;
        int lmax = linit + Camera::screenSize.x / associated.box.w;
        if (Camera::screenSize.x - associated.box.x >
            (lmax + 1) * associated.box.w)
            lmax++;

        for (int i = linit; i <= lmax; i++) {
            Rect dst(associated.box.pos.x + i * width, associated.box.pos.y,
                     (double)width, (double)height);
            SDL_Rect dstRect = dst;
            SDL_Rect clipRect = Rect(Vec2(0, 0), associated.box.size);
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture.get(),
                           &clipRect, &dstRect);
        }
    }
}