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

State::State() : input(InputManager::getInstance()) {}

std::weak_ptr<GameObject> State::add_object(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    object_array.emplace_back(ptr);
    if (started) ptr->start();

    return ptr;
}

std::weak_ptr<GameObject> State::get_object_ptr(GameObject* go) {
    std::weak_ptr<GameObject> wp;
    for (std::shared_ptr<GameObject>& obj : object_array) {
        if (obj.get() == go) {
            wp = obj;
            break;
        }
    }

    return wp;
}

void State::start_array() {
    if (started) return;

    //    for (auto obj : object_array) obj->Start();
    for (size_t i = 0; i < object_array.size(); i++) object_array[i]->Start();

    started = true;
}

void State::UpdateArray(float delta_time) {
    // Update
    //    for (auto obj : objectArray) obj->Update(delta_time);
    for (size_t i = 0; i < objectArray.size(); i++) objectArray[i]->Update(delta_time);

    // Delete
    auto removeDead = [&](std::shared_ptr<GameObject> const& p) {
        return p->IsDead() && p->canEnd();
    };
    object_array.erase(
        std::remove_if(object_array.begin(), object_array.end(), remove_dead),
        object_array.end());

    // KeyPress
    if (input.actionPress(input.ESCAPE) || input.QuitRequested())
        quitRequested = true;
}

void State::rhythmUpdateArray() {
    for (auto obj : objectArray) obj->rhythmUpdate();
}

void State::rhythmResetArray() {
    for (auto obj : object_array) obj->rhythmReset();
}

float fix_range_2(float value, float fix) {
    float ret = value + fix;
    if (ret > 1.0)
        ret -= 2;
    else if (ret < -1.0)
        ret += 2;

    return ret;
}

int pulse_color(float dtr, int combo) {
    static const int minColor = 10;
    dtr = fix_range_2(dtr, 1);
    dtr = (dtr > 0) ? 0 : -dtr;
    combo = (combo > 15) ? 15 : combo;
    dtr = dtr * 2 * (combo * 10 + 10) + minColor;
    dtr = (dtr < 0) ? 0 : dtr;
    return (dtr > 255) ? 255 : dtr;
}

void State::RenderLight() const {
    SDL_Renderer* renderer = Game::getInstance()->GetRenderer();

    // Rendering default layer to texture
    static SDL_Texture* tex_default = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        Camera::screen_size.x, Camera::screen_size.y);
    SDL_SetRenderTarget(renderer, tex_default);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (auto obj : object_array) {
        obj->render_order(Common::Layer::DEFAULT);
    }

    // Rendering to texture (Lights to an texture)
    static SDL_Texture* tex_light = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        Camera::screen_size.x, Camera::screen_size.y);

    SDL_SetRenderTarget(renderer, tex_light);

    int color = pulse_color(input.get_delta_rhythm(), Game::get_instance()->combo);
    SDL_SetRenderDrawColor(renderer, color, color, color * 0.8, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    for (auto obj : object_array) {
        obj->render_order(Common::Layer::LIGHT);
    }

    // Rendering the texture to screen (multiply light texture to screen)
    SDL_SetRenderTarget(renderer, tex_default);

    SDL_SetTextureBlendMode(tex_default, SDL_BLENDMODE_MOD);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MOD);
    SDL_SetTextureBlendMode(tex_light, SDL_BLENDMODE_MOD);
    SDL_RenderCopy(renderer, tex_light, NULL, NULL);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(tex_default, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, tex_default, NULL, NULL);
}

void State::renderArray() const {
    for (auto obj : objectArray) {
        obj->renderOrder(Common::Layer::BG);
    }

    render_light();

    for (auto obj : object_array) {
        if (!obj->blink) {
            obj->renderOrder(Common::Layer::HUD);
        } else {
            if (input.shouldShow) obj->renderOrder(Common::Layer::HUD);
        }
    }
}
