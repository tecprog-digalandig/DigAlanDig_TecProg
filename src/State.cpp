#include "State.h"
#include <stdio.h>
#include "Face.h"
#include "SDL2/SDL.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

#define UNUSED_VAR (void)

State::State(void) : quitRequested(false) {
    GameObject* gm = new GameObject();
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/ocean.jpg"));
    tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    gm->AddComponent(new TileMap(*gm, "assets/map/tileMap.txt", tileSet));
    music = new Music("assets/audio/stageState.ogg");
    music->Play(2);
}

void State::Update(float dt) {
    Input();
    for (auto& obj : objectArray) obj->Update(dt);

    auto removeDead = [&](std::unique_ptr<GameObject> const& p) {
        return p->IsDead() && p->CanEnd();
    };

    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(), removeDead),
        objectArray.end());
}

void State::Render() {
    for (auto& obj : objectArray) obj->Render();
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* gm = new GameObject();
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/penguinface.png"));
    gm->AddComponent(new Sound(*gm, "assets/audio/boom.wav"));
    gm->AddComponent(new Face(*gm));

    std::cout << "New Object" << std::endl;
    gm->box.pos.set(mouseX - gm->box.w / 2, mouseY - gm->box.h / 2);
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {
        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Percorrer de trás pra frente pra sempre clicar no objeto mais de
            // cima
            for (int i = objectArray.size() - 1; i >= 0; --i) {
                // Obtem o ponteiro e casta pra Face.
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao
                // máximo. O propósito do unique_ptr é manter apenas uma cópia
                // daquele ponteiro, ao usar get(), violamos esse princípio e
                // estamos menos seguros. Esse código, assim como a classe Face,
                // é provisório. Futuramente, para chamar funções de
                // GameObjects, use objectArray[i]->função() direto.

                GameObject* go = (GameObject*)objectArray[i].get();
                if (go->box.IsInside((double)mouseX, (double)mouseY)) {
                    Face* face = (Face*)go->GetComponent("Face");
                    if (nullptr != face) {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else {
                Vec2 objPos =
                    Vec2(200, 0).rotate(rand() % 361) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}
