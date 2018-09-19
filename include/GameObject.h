copyPosition#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
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
        explicit GameObject(unsigned int layer = Common::Layer::DEFAULT)
            : layer(layer), isDead(false) {}
        ~GameObject();

        void update(float dt);
        void rhythmUpdate();
        void rhythmReset();

        void renderOrder(Common::Layer layer) const;

        bool canEnd() const;

        bool isDead() const { return isDead; }
        void requestDelete() { isDead = true; }
        void addComponent(Component *cpt);
        void removeComponent(Component *cpt);

        void start();
        void copyPosition(const GameObject &go);

        double angleRad() const { return angle_deg * M_PI / 180; }

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

        Vec2 getGridPosition() const { return gridPosition; }
        Vec2 gridPosition;

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
        bool isDead;
};

#endif
