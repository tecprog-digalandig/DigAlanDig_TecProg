#ifndef ALAN_H
#define ALAN_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "AlanActionControl.h"
#include "Component.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

class Alan : public Component 
{
  public:
    explicit Alan(GameObject& associated);

    ~Alan() {}

    void getMovement();

    void update(float delta_time);

    void rhythmUpdate() {}

    void rhythmReset() 
    {
        static int miss_counter = 0;
        if (!moved)
            miss_counter++;
        else
            miss_counter = 0;

        if (miss_counter > 1) 
        {
            Game::getInstance()->combo /= 2;
        }

        moved = false;
        damage_taken = false;
    }
    void render(Common::layer layer) const {}

    int getMaxPosition() const 
    { 
        return max_position; 
    }

    Vec2 getGridPosition() 
    { 
        return associated.getGridPosition(); 
    }

    AlanActionControl::direction getMovementDirection() 
    {
        return associated.getComponent<AlanActionControl*>()
            ->getMovementDirection();
    }

    AlanActionControl::Action getAction() 
    {
        return associated.getComponent<AlanActionControl*>()->getAction();
    }

    int getDamage() 
    { 
        return damage; 
    }

    void takeDamage() 
    {
        if (!damage_taken) 
        {
            //life_enemy--;
            damage_taken = true;
        }
    }

    void setDamage(int damage) 
    { 
        //this->damage = damage; 
    }

    int getHP() 
    { 
        return life_enemy; 
    }

    void setItemCount(GameObject* go) 
    { 
        item_count = go; 
    }

    GameObject* getItemCount() 
    { 
        return item_count; 
    }

  private:
    GameObject* item_count;
    const int life_enemy = 6;

    int max_position = 0;
    int grids_left = 0;

    InputManager& input;

    const int damage = 1;

    bool moved = false;
    bool damage_taken = false;
    bool animation_on_going = false;
};

#endif  // ALAN_H
