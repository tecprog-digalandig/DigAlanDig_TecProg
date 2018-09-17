#include "AlanItemCount.h"
#include "Common.h"

AlanItemCount::alanItemCount(GameObject& associated) : Component(associated) 
{
    itemCount.emplace(Common::ItemType::gold, rand() % 5);
    itemCountItem.emplace(Common::ItemType::gold,
                          new gameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::gold]->box.x = 950;
    itemCountItem[Common::ItemType::gold]->box.y = 115;
    itemCountItem[Common::ItemType::gold]->world_reference = false;
    Sprite* sprite = new sprite(*itemCountItem[Common::ItemType::gold],
                                "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::gold]->addComponent(sprite);
    itemCountItem[Common::ItemType::gold]->addComponent(new Item(
        *itemCountItem[Common::ItemType::gold],
        itemCountItem[Common::ItemType::gold]->box.Center(),
        vec2(itemCountItem[Common::ItemType::gold]->box.Center().x + 20,
             itemCountItem[Common::ItemType::gold]->box.Center().y + 5)));
    std::cout << "gold COUNT = " << itemCount[Common::ItemType::gold]
              << std::endl;
    sprite->setFrame(itemCount[Common::ItemType::gold]);

    itemCount.emplace(Common::ItemType::diamond, rand() % 5 + 4);
    itemCountItem.emplace(Common::ItemType::diamond,
                          new gameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::diamond]->box.x = 950;
    itemCountItem[Common::ItemType::diamond]->box.y = 263;
    itemCountItem[Common::ItemType::diamond]->world_reference = false;
    sprite = new sprite(*itemCountItem[Common::ItemType::diamond],
                        "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::diamond]->addComponent(sprite);
    itemCountItem[Common::ItemType::diamond]->addComponent(new Item(
        *itemCountItem[Common::ItemType::diamond],
        itemCountItem[Common::ItemType::diamond]->box.Center(),
        vec2(itemCountItem[Common::ItemType::diamond]->box.Center().x + 20,
             itemCountItem[Common::ItemType::diamond]->box.Center().y + 5)));
    sprite->setFrame(itemCount[Common::ItemType::diamond]);

    itemCount.emplace(Common::ItemType::petroleum, rand() % 5 + 4);
    itemCountItem.emplace(Common::ItemType::petroleum,
                          new gameObject(Common::Layer::HUD));
    itemCountItem[Common::ItemType::petroleum]->box.x = 950;
    itemCountItem[Common::ItemType::petroleum]->box.y = 415;
    itemCountItem[Common::ItemType::petroleum]->world_reference = false;
    sprite = new sprite(*itemCountItem[Common::ItemType::petroleum],
                        "assets/hud/numbers.png", 10, -2);
    itemCountItem[Common::ItemType::petroleum]->addComponent(sprite);
    itemCountItem[Common::ItemType::petroleum]->addComponent(new Item(
        *itemCountItem[Common::ItemType::petroleum],
        itemCountItem[Common::ItemType::petroleum]->box.Center(),
        vec2(itemCountItem[Common::ItemType::petroleum]->box.Center().x + 20,
             itemCountItem[Common::ItemType::petroleum]->box.Center().y + 5)));
    sprite->setFrame(itemCount[Common::ItemType::petroleum]);
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
