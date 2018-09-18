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

// Item Class characteristics and heritages.
class Item : public Component 
{
    public:
        Item(GameObject& associated, Vec2 newCenter, Vec2 newNumberCenter)
        : Component(associated),
          center(newCenter),
          numberCenter(newNumberCenter) 
        {
            bg = new sprite(associated, "assets/hud/ovocinza.png");
        }

        ~Item() 
        { 
            delete bg; 
        }

        void update(float dt) {}

        void rhythmUpdate() {}

        void rhythmReset() {}

        void render(Common::Layer layer) const {}

        Sprite* bg;
        Vec2 center, number_center;
        int sprite_count = 1;
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
        //Update according to dt.
	    //@param dt: Delta time. Time elapsed between one frame and the other.
        void update(float dt) {}

        void rhythmUpdate() {}

        void rhythmReset() {}

        void render(Common::Layer layer) const;

        void itemCollected(int item_type) 
        {
            if (itemCount[item_type] > 0)
            itemCountItem[item_type]->getComponent<Sprite*>()->setFrame(
                --itemCount[item_type]);
        }

        bool collectedAllItens() 
        {
            if (itemCount[Common::ItemType::diamond] == 0 &&
                itemCount[Common::ItemType::petroleum] == 0 &&
                itemCount[Common::ItemType::gold] == 0)
            return true;

            return false;
        }

    private:
    std::unordered_map<int, GameObject*> item_count_item;
    std::unordered_map<int, int> item_count;
};

#endif  // ALANITEMCOUNT_H
