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
#include <vector>
#include "Component.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"

class Item : public Component 
{
    public:
        Item(GameObject& associated, Vec2 newCenter, Vec2 newNumberCenter)
        : Component(associated),
          center(newCenter),
          numberCenter(newNumberCenter) 
        {
            //bg = new Sprite(associated, "assets/hud/ovocinza.png");
        }

        ~Item() 
        { 
            delete bg; 
        }

        void Update(float delta_time) {}

        void rhythmUpdate() {}

        void rhythmReset() {}

        void render(Common::Layer layer) const {}

        Sprite* bg;
        Vec2 center, numberCenter;
        int Sprite_count = 1;
};

class AlanItemCount : public Component 
{
    public:
        AlanItemCount(GameObject& associated);

        ~AlanItemCount() 
        {
            item_count.clear();
            item_count_item.clear();
        }

        void Update(float delta_time) {}

        void rhythmUpdate() {}

        void rhythmReset() {}

        void render(Common::Layer layer) const;

        void itemCollected(int item_type) 
        {
            if (item_count[item_type] > 0)
            item_count_item[item_type]->GetComponent<Sprite*>()->setFrame(
                --item_count[item_type]);
        }

        bool collectedAllItens() 
        {
            if (item_count[Common::ItemType::diamond] == 0 &&
                item_count[Common::ItemType::petroleum] == 0 &&
                item_count[Common::ItemType::gold] == 0)
            return true;

            return false;
        }

    private:
    std::unordered_map<int, GameObject*> item_count_item;
    std::unordered_map<int, int> item_count;
};

#endif  // ALANITEMCOUNT_H
