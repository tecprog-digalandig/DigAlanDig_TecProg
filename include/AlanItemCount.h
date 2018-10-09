#ifndef ALANITEMCOUNT_H
#define ALANITEMCOUNT_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <queue>
#include <string>
#include "Component.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"

class Item : public Component {
  public:
    Item(GameObject& associated, Vec2 newCenter, Vec2 newNumberCenter)
        : Component(associated),
          center(newCenter),
          numberCenter(newNumberCenter) {
        bg = new Sprite(associated, "assets/hud/ovocinza.png");
    }

    ~Item() { delete bg; }
    void Update(float dt) {}
    void RhythmUpdate() {}
    void RhythmReset() {}
    void Render(Common::Layer layer) const {}

    Sprite* bg;
    Vec2 center, numberCenter;
    int spriteCount = 1;
};

class AlanItemCount : public Component {
  public:
    AlanItemCount(GameObject& associated);

    ~AlanItemCount() {
        itemCount.clear();
        itemCountItem.clear();
    }

    void Update(float dt) {}
    void RhythmUpdate() {}
    void RhythmReset() {}
    void Render(Common::Layer layer) const;
    void ItemCollected(int itemType) {
        if (itemCount[itemType] > 0)
            itemCountItem[itemType]->GetComponent<Sprite*>()->SetFrame(
                --itemCount[itemType]);
    }
    bool CollectedAllItens() {
        if (itemCount[Common::ItemType::DIAMOND] == 0 &&
            itemCount[Common::ItemType::PETROLEUM] == 0 &&
            itemCount[Common::ItemType::GOLD] == 0)
            return true;

        return false;
    }

  private:
    std::unordered_map<int, GameObject*> itemCountItem;
    std::unordered_map<int, int> itemCount;
};

#endif  // ALANITEMCOUNT_H
