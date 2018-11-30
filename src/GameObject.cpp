/**
* @file GameObject.cpp
* @copyright 2018 Pedro H.
* @brief Class that create, move, update and render objects on the screen.
*/

#include "GameObject.h"
#include "Sound.h"
#include <assert.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

GameObject::~GameObject()
{
    for (Component* component : components) delete (component);

    components.clear();
    tmp = box;
}

void GameObject::start()
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in GameObject::start");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("Game Object successfully started");

        if (started)
        {
            return;
        }
        else
        {
            //Nothing to do
        }
        for (auto c : components) c->start();

        started = true;
    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }

}

bool GameObject::canEnd() const { return true; }

void GameObject::update(float dt)
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in GameObject::update ");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("GameObject successfully updated");

        static float sum;
        assert(sum >= 0);
        sum += dt;
        for (Component* component : components) component->update(dt);
        if (move)
        {
            box.pos = tmp.pos + Vec2(0, 1) * sin(sum) * 30;
        }
        else
        {
            //Nothing to do
        }

    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

//Keeps the game flowing
void GameObject::rhythmUpdate()
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in GameObject::rhythmUpdate ");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("GameObject rhythm successfully updated");

        for (Component* component : components) component->rhythmUpdate();

    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

//Reset the rate of the rhythm
void GameObject::rhythmReset()
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in GameObject::rhythmReset ");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("GameObject rhythm successfully reseted");

        for (Component* component : components) component->rhythmReset();

    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

//Sets the order that objects are rendered on the screen
void GameObject::renderOrder(Common::Layer layer) const
{
    try
    {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");

        spd::set_level(spd::level::info); // Set global log level to info
        console->debug("Error in GameObject::renderOrder");
        console->set_level(spd::level::debug); // Set specific logger's log level
        console->debug("GameObject::renderOrder accessed");

        if (!(this->layer & layer))
        {
            return;
        }
        else
        {
            //Nothing to do
        }
        for (Component* component : components) component->render(layer);

    }
    catch(const spd::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}

/**
* @brief Removing blocks when Alan digs it
* @param [in] cpt is a Component pointer
*/
void GameObject::removeComponent(Component* cpt)
{
    components.erase(std::remove(components.begin(), components.end(), cpt),
    components.end());
}

void GameObject::addComponent(Component* cpt) { components.emplace_back(cpt); }

void GameObject::copyPosition(const GameObject& go)
{
    assert(go != nullptr);
    box = go.box;
    world_reference = go.world_reference;
    from_player = go.from_player;
    angle_deg = go.angle_deg;
}
