#include "State.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <stdio.h>
#include "Camera.h"
#include "Common.h"
#include "Game.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

State::State() : input(InputManager::GetInstance()) {}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.emplace_back(ptr);
    if (started) ptr->start();

    return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPrt(GameObject* go) {
    std::weak_ptr<GameObject> wp;
    for (std::shared_ptr<GameObject>& obj : objectArray) {
        if (obj.get() == go) {
            wp = obj;
            break;
        }
    }

    return wp;
}

void State::StartArray() {
    if (started) return;

    //    for (auto obj : objectArray) obj->Start();
    for (size_t i = 0; i < objectArray.size(); i++) objectArray[i]->start();

    started = true;
}

void State::UpdateArray(float dt) {
    // Update
    //    for (auto obj : objectArray) obj->update(dt);
    for (size_t i = 0; i < objectArray.size(); i++) objectArray[i]->update(dt);

    // Delete
    auto removeDead = [&](std::shared_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());

    // KeyPress
    if (input.ActionPress(input.ESCAPE) || input.QuitRequested())
        quitRequested = true;
}

void State::RhythmUpdateArray() {
    for (auto obj : objectArray) obj->rhythmUpdate();
}

void State::RhythmResetArray() {
    for (auto obj : objectArray) obj->RhythmReset();
}

float fixRange2(float value, float fix) {
    float ret = value + fix;
    if (ret > 1.0)
        ret -= 2;
    else if (ret < -1.0)
        ret += 2;

    return ret;
}

int PulseColor(float dtR, int combo) {
    static const int minColor = 10;
    dtR = fixRange2(dtR, 1);
    dtR = (dtR > 0) ? 0 : -dtR;
    combo = (combo > 15) ? 15 : combo;
    dtR = dtR * 2 * (combo * 10 + 10) + minColor;
    dtR = (dtR < 0) ? 0 : dtR;
    return (dtR > 255) ? 255 : dtR;
}

void State::RenderLight() const {
    SDL_Renderer* renderer = Game::GetInstance()->GetRenderer();

    // Rendering default layer to texture
    static SDL_Texture* texDefault = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        Camera::screenSize.x, Camera::screenSize.y);
    SDL_SetRenderTarget(renderer, texDefault);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (auto obj : objectArray) {
        obj->RenderOrder(Common::Layer::DEFAULT);
    }

    // Rendering to texture (Lights to an texture)
    static SDL_Texture* texLight = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        Camera::screenSize.x, Camera::screenSize.y);

    SDL_SetRenderTarget(renderer, texLight);

    int color = PulseColor(input.GetDeltaRhythm(), Game::GetInstance()->combo);
    SDL_SetRenderDrawColor(renderer, color, color, color * 0.8, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    for (auto obj : objectArray) {
        obj->RenderOrder(Common::Layer::LIGHT);
    }

    // Rendering the texture to screen (multiply light texture to screen)
    SDL_SetRenderTarget(renderer, texDefault);

    SDL_SetTextureBlendMode(texDefault, SDL_BLENDMODE_MOD);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MOD);
    SDL_SetTextureBlendMode(texLight, SDL_BLENDMODE_MOD);
    SDL_RenderCopy(renderer, texLight, NULL, NULL);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(texDefault, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, texDefault, NULL, NULL);
}

void State::RenderArray() const {
    for (auto obj : objectArray) {
        obj->RenderOrder(Common::Layer::BG);
    }

    RenderLight();

    for (auto obj : objectArray) {
        if (!obj->blink) {
            obj->RenderOrder(Common::Layer::HUD);
        } else {
            if (input.shouldShow) obj->RenderOrder(Common::Layer::HUD);
        }
    }
}
