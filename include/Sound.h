#ifndef SOUND_H
#define SOUND_H
#include "Component.h"
#define INCLUDE_SDL_MIXER
#include "Resources.h"
#include "SDL_include.h"

class Sound : public Component {
  public:
    Sound(GameObject& associated)
        : Component(associated), chunk(nullptr), played(false) {}
    Sound(GameObject& associated, std::string file)
        : Component(associated), chunk(nullptr), played(false) {
        Open(file);
    }

    ~Sound() { Stop(); }

    void Open(std::string file) { chunk = Resources::GetSound(file); }
    bool IsOpen(void) { return (bool)chunk; }
    bool CanEnd(void) { return played && !Mix_Playing(channel); }
    void Play(int times = 1);
    void Stop() {
        if (chunk) Mix_HaltChannel(channel);
    }

    void Update(float dt) {}
    void Render() {}
    bool Is(std::string type) { return !type.compare("Sound"); }

  private:
    Mix_Chunk* chunk;
    int channel;
    bool played;
};

#endif  // SOUND_H
