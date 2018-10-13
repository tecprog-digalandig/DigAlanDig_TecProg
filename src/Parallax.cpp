#include <assert.h>
#include "Parallax.h"
#include "Game.h"
#include "Resources.h"


/**
 * @brief open file of texture circular background on axis Y
 * 
 * @param file 
 */
void bgCircularY::Open(const std::string &file) 
{
    texture = Resources::GetImage(file);
    assert(texture != NULL);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.size.Set(width, height);
}

/**
 * @brief  rendering layers of circular background on axis Y
 * 
 * @param layer 
 */
void bgCircularY::render(Common::Layer layer) const 
{
    if (bgCircularY::texture) 
    {
        int l_init = -associated.box.y / associated.box.h;
        int l_max = l_init + Camera::screenSize.y / associated.box.h;


        assert(l_init > 0);
        assert(l_max > 0);

        if (Camera::screenSize.y - associated.box.y >
            (l_max + 1) * associated.box.h)
            l_max++;

        for (int i = l_init; i <= l_max; i++) 
        {
            Rect dst(associated.box.pos.x, associated.box.pos.y + i * height,
                     (double)width, (double)height);
            SDL_Rect dstRect = dst;
            SDL_Rect clipRect = Rect(Vec2(0, 0), associated.box.size);
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture.get(),
                           &clipRect, &dstRect);
        }
    }
}

/**
 * @brief open file of texture circular background on axis X
 * 
 * @param file 
 */
void bgCircularX::Open(const std::string &file) 
{
    texture = Resources::GetImage(file);
    assert(texture != NULL);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.size.Set(width, height);
}

/**
 * @brief  rendering layers of circular background on axis X
 * 
 * @param layer 
 */
void bgCircularX::render(Common::Layer layer) const 
{
    if (bgCircularX::texture) 
    {
        int l_init = -associated.box.x / associated.box.w;
        int l_max = l_init + Camera::screenSize.x / associated.box.w;

        assert(l_init > 0);
        assert(l_max > 0);

        if (Camera::screenSize.x - associated.box.x >
            (l_max + 1) * associated.box.w)
            l_max++;

        for (int i = l_init; i <= l_max; i++) 
        {
            Rect dst(associated.box.pos.x + i * width, associated.box.pos.y,
                     (double)width, (double)height);
            SDL_Rect dstRect = dst;
            SDL_Rect clipRect = Rect(Vec2(0, 0), associated.box.size);
            SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture.get(),
                           &clipRect, &dstRect);
        }
    }
}