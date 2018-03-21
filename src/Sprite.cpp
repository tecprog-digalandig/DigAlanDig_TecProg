#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(void):
    texture(nullptr)
{
}

Sprite::Sprite(std::string file):
    texture(nullptr)
{
    Sprite::Open(file);
}

Sprite::~Sprite(void)
{
    if (Sprite::texture)
        SDL_DestroyTexture(Sprite::texture);
}

void Sprite::Open(std::string file)
{
    if (Sprite::texture)
        SDL_DestroyTexture(texture);

    Sprite::texture =
            IMG_LoadTexture(Game::getInstance()->getRenderer(), file.c_str());
    if (!Sprite::texture)
    {
        std::cerr << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}


void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y)
{
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    dstRect.x = x;
    dstRect.y = y;

    if(IsOpen())
        SDL_RenderCopy(Game::getInstance()->getRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth(void)
{
    return width;
}

int Sprite::GetHeight(void)
{
    return height;
}

bool Sprite::IsOpen(void)
{
    if (Sprite::texture)
        return true;
    return false;
}

