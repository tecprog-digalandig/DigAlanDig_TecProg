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
#include "AlanActionControl.h"
#include "Component.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Vec2.h"

// Alan characteristics.
class Alan : public Component 
{
  public:
    explicit Alan(GameObject& associated);

    //Destructor.
    ~Alan() {}

    void getMovement();

    
	//Update according to dt.
	//@param dt: Delta time. Time elapsed between one frame and the other.
    void update(float dt);

    void rhythmUpdate() {}

    void rhythmReset() 
    {
        static int missCounter = 0;
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
	//Render according to the layer.
    void render(Common::Layer layer) const {}

    //Getters & Setters Methods.
    int getMaxPosition() const 
    { 
        return max_position; 
    }

    Vec2 getGridPosition() 
    { 
        return associated.getGridPosition(); 
    }

    AlanActionControl::Direction getMovementDirection() 
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
        return DAMAGE; 
    }

    void takeDamage() 
    {
        if (!damage_taken) 
        {
            HP--;
            damage_taken = true;
        }
    }

    void setDamage(int DAMAGE) 
    { 
        this->damage = DAMAGE; 
    }

    int getHP() 
    { 
        return HP; 
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
    const int HP = 6;

    int max_position = 0;
    int grids_left = 0;

    InputManager& input;

    const int DAMAGE = 1;

    bool moved = false;
    bool damage_taken = false;
    bool animation_on_going = false;
};

#endif  // ALAN_H
