#include "GameObject.h"
#include "Sound.h"

bool GameObject::CanEnd() {
    if (Sound* sound = (Sound*)GetComponent("Sound"))
        return sound->CanEnd();
    return false;
}

GameObject::~GameObject() {
    for (Component* component : components) delete (component);

    components.clear();
}

void GameObject::Update(float dt) {
    // TODO: parallel_for, opemmp fop_each
    for (Component* component : components) component->Update(dt);
}

void GameObject::Render() {
    for (Component* component : components) component->Render();
}

void GameObject::RemoveComponent(Component* cpt) {
    // CHECK: delete cpt?
    components.erase(std::remove(components.begin(), components.end(), cpt),
                     components.end());
}

Component* GameObject::GetComponent(std::string type) {
    for (Component* component : components)
        if (component->Is(type)) return component;

    return nullptr;
}
