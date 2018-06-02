#include "Endstate.h"
#include "Game.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Text.h"

EndState::EndState() {}

void EndState::LoadAssets() {
    GameObject* gm = new GameObject();
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    if (Game::GetInstance()->playerVictory) {
        gm->AddComponent(new Sprite(*gm, "assets/img/win.jpg"));
        music = Music("assets/audio/endStateWin.ogg");
    } else {
        gm->AddComponent(new Sprite(*gm, "assets/img/lose.jpg"));
        music = Music("assets/audio/endStateLose.ogg");
    }

    music.Play(2);
}

void EndState::Start() {
    if (!started) LoadAssets();

    StartArray();
}

void EndState::Update(float dt) { UpdateArray(dt); }

void EndState::Render() const { RenderArray(); }
