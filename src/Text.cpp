#include "Text.h"
#include "Game.h"
#include "Resources.h"

Text::Text(GameObject& associated, const std::string& fontFile, int fontSize,
           TextStyle style, const std::string& text, SDL_Color color, int timer)
    : Component(associated),
      fontFile(fontFile),
      fontSize(fontSize),
      style(style),
      text(text),
      color(color),
      totalTime(timer) {
    font = Resources::GetFont(fontFile, fontSize);

    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) SDL_DestroyTexture(texture);
}

void Text::Update(float dt) {
    if (totalTime <= 0) return;

    timer.Update(dt);
    if (timer.Get() >= totalTime) {
        display = !display;
        timer.Restart();
    }
}

void Text::Render() const {
    if (!texture) return;

    Vec2 offset;
    if (associated.worldReference) offset = Camera::pos;
    Rect dst(associated.box.pos - offset, associated.box.size);

    SDL_Rect dstRect = dst;
    SDL_Rect clipRect = dst;
    clipRect.x = clipRect.y = 0;

    if (display)
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, &clipRect,
                       &dstRect);
}

void Text::SetFontFile(const std::string& fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetText(const std::string& text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::RemakeTexture() {
    SDL_Surface* surface = nullptr;
    if (texture != nullptr) SDL_DestroyTexture(texture);

    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case SHADED:
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color,
                                            {0, 0, 0, 255});
            break;
        case BLENDED:
            surface = TTF_RenderText_Blended_Wrapped(font.get(), text.c_str(),
                                                     color, associated.box.w);
            break;
    }
    Vec2 center = associated.box.Center();
    associated.box.size = Vec2(surface->w, surface->h);
    associated.box.SetCenter(center);

    texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(),
                                           surface);
    SDL_FreeSurface(surface);
}
