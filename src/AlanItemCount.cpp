#include "AlanItemCount.h"
#include "Common.h"

AlanItemCount::alanItemCount(GameObject& associated) : Component(associated) 
{
    itemCount.emplace(Common::ItemType::GOLD, rand() % 5);
    itemCountItem.emplace(Common::ItemType::GOLD,
                          new gameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::GOLD]->box.x = 950;
    itemCountItem[Common::ItemType::GOLD]->box.y = 115;
    itemCountItem[Common::ItemType::GOLD]->worldReference = false;
    Sprite* sprite = new sprite(*itemCountItem[Common::ItemType::GOLD],
                                "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::GOLD]->addComponent(sprite);
    itemCountItem[Common::ItemType::GOLD]->addComponent(new Item(
        *itemCountItem[Common::ItemType::GOLD],
        itemCountItem[Common::ItemType::GOLD]->box.Center(),
        vec2(itemCountItem[Common::ItemType::GOLD]->box.Center().x + 20,
             itemCountItem[Common::ItemType::GOLD]->box.Center().y + 5)));
    std::cout << "GOLD COUNT = " << itemCount[Common::ItemType::GOLD]
              << std::endl;
    sprite->setFrame(itemCount[Common::ItemType::GOLD]);

    itemCount.emplace(Common::ItemType::DIAMOND, rand() % 5 + 4);
    itemCountItem.emplace(Common::ItemType::DIAMOND,
                          new gameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::DIAMOND]->box.x = 950;
    itemCountItem[Common::ItemType::DIAMOND]->box.y = 263;
    itemCountItem[Common::ItemType::DIAMOND]->worldReference = false;
    sprite = new sprite(*itemCountItem[Common::ItemType::DIAMOND],
                        "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::DIAMOND]->addComponent(sprite);
    itemCountItem[Common::ItemType::DIAMOND]->addComponent(new Item(
        *itemCountItem[Common::ItemType::DIAMOND],
        itemCountItem[Common::ItemType::DIAMOND]->box.Center(),
        vec2(itemCountItem[Common::ItemType::DIAMOND]->box.Center().x + 20,
             itemCountItem[Common::ItemType::DIAMOND]->box.Center().y + 5)));
    sprite->setFrame(itemCount[Common::ItemType::DIAMOND]);

    itemCount.emplace(Common::ItemType::PETROLEUM, rand() % 5 + 4);
    itemCountItem.emplace(Common::ItemType::PETROLEUM,
                          new gameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::PETROLEUM]->box.x = 950;
    itemCountItem[Common::ItemType::PETROLEUM]->box.y = 415;
    itemCountItem[Common::ItemType::PETROLEUM]->worldReference = false;
    sprite = new sprite(*itemCountItem[Common::ItemType::PETROLEUM],
                        "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::PETROLEUM]->addComponent(sprite);
    itemCountItem[Common::ItemType::PETROLEUM]->addComponent(new Item(
        *itemCountItem[Common::ItemType::PETROLEUM],
        itemCountItem[Common::ItemType::PETROLEUM]->box.Center(),
        vec2(itemCountItem[Common::ItemType::PETROLEUM]->box.Center().x + 20,
             itemCountItem[Common::ItemType::PETROLEUM]->box.Center().y + 5)));
    sprite->setFrame(itemCount[Common::ItemType::PETROLEUM]);
}

void AlanItemCount::render(Common::Layer layer) const 
{
    for (auto item : itemCountItem) 
    {
        item.second->box.setCenter(item.second->getComponent<Item*>()->center);

        if (!itemCount.at(item.first)) 
        {
            item.second->getComponent<Item*>()->bg->setColor(0, 255, 0);
        }

        item.second->getComponent<Item*>()->bg->render(layer);

        item.second->getComponent<Item*>()->bg->setColor(255, 255, 255);

        item.second->box.setCenter(
            item.second->getComponent<Item*>()->numberCenter);
        item.second->renderOrder(layer);
    }
}
