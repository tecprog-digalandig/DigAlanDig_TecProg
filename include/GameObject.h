#ifndef GameObject_H
#define GameObject_H
#include <algorithm>
#include <memory>
#include <vector>
#include "Common.h"
#include "Component.h"
#include "Rect.h"

class Component;

class GameObject
{
    public:
        explicit GameObject(unsigned int layer = Common::layer::DEFAULT)
            : layer(layer), is_dead(false) {}
        ~GameObject();

    void update(float delta_time);
    void rhythmUpdate();
    void rhythmReset();

    void renderOrder(Common::layer layer) const;

    bool canEnd() const;

    bool isDead() const { return isDead; }
    void requestDelete() { is_dead = true; }
    void addComponent(Component *cpt);
    void removeComponent(Component *cpt);

    void start();
    void copyPosition(const GameObject &go);

        double angleRad() const 
        { 
            return angle_deg * M_PI / 180; 
        }

        template <class T>
        T getComponent() const
        {
            for (Component *component : components)
            {
                if (T t = dynamic_cast<T>(component))
                {
                    return t;
                }
            }
            return nullptr;
        }

        Vec2 getGridPosition() const 
        { 
            return grid_position; 
        }

        Vec2 grid_position;

        Rect box;
        bool world_reference = true;
        bool blink = false;
        bool move = false;
        bool from_player = false;
        bool started = false;
        double angle_deg = 0;
        unsigned int layer;

        void setRect(Rect a) { tmp = a; }
        Rect tmp;

    private:
        std::vector<Component *> components;
        bool is_dead;
};

#endif  // GameObject_H
