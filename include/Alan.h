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

class Alan : public Component 
{
  public:
    explicit Alan(GameObject& associated);

    ~Alan() {}

    void getMovement();

    void update(float dt);

    void rhythmUpdate() {}

    void rhythmReset() 
    {
        static int missCounter = 0;
        if (!moved)
            missCounter++;
        else
            missCounter = 0;

        if (missCounter > 1) 
        {
            Game::getInstance()->combo /= 2;
        }

        moved = false;
        damageTaken = false;
    }
    void render(Common::Layer layer) const {}

    int getMaxPosition() const 
    { 
        return maxPosition; 
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
        return damage; 
    }

    void takeDamage() 
    {
        if (!damageTaken) 
        {
            hp--;
            damageTaken = true;
        }
    }

    void setDamage(int damage) 
    { 
        this->damage = damage; 
    }

    int getHP() 
    { 
        return hp; 
    }

    void setItemCount(GameObject* go) 
    { 
        itemCount = go; 
    }

    GameObject* getItemCount() 
    { 
        return itemCount; 
    }

  private:
    GameObject* itemCount;
    int hp = 6;

    int maxPosition = 0;
    int gridsLeft = 0;

    InputManager& input;

    int damage = 1;

    bool moved = false;
    bool damageTaken = false;
    bool animationOnGoing = false;
};

#endif  // ALAN_H
