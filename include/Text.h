#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "Component.h"
#include "Timer.h"

class Text : public Component {
  public:
    enum TextStyle { SOLID, SHADED, BLENDED };
    Text(GameObject& associated, const std::string& fontFile, int fontSize,
         TextStyle style, const std::string& text, SDL_Color color,
         int timer = -1);
    ~Text();

    void Update(float dt);
    void Render() const;
    bool Is(const std::string& type) const { return !type.compare("Text"); }

    void SetFontFile(const std::string& fontFile);
    void SetFontSize(int fontSize);
    void SetStyle(TextStyle style);
    void SetText(const std::string& text);
    void SetColor(SDL_Color color);

  private:
    void RemakeTexture();

    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture = nullptr;

    std::string fontFile;
    int fontSize;
    TextStyle style;
    std::string text;
    SDL_Color color;

    int totalTime;
    Timer timer;
    bool display = true;
};

#endif  // TEXT_H
