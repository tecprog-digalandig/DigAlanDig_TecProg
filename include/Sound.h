#ifndef SOUND_H
#define SOUND_H
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"
#include "Resources.h"

class Sound : public Component {
  public:
    explicit Sound(GameObject& associated)
        : Component(associated), chunk(nullptr), played(false) {}
    Sound(GameObject& associated, const std::string& file, bool play = false)
        : Component(associated), chunk(nullptr), played(false) {
        Open(file);
        if (play) Play();
    }

    ~Sound() { Stop(); }

    void Open(const std::string& file) { chunk = Resources::GetSound(file); }
    bool IsOpen() const { return (bool)chunk; }
    bool CanEnd() const { return played && !Mix_Playing(channel); }
    void Play(int times = 1);
    void Stop() const {
        if (chunk) Mix_HaltChannel(channel);
    }
    void SetVolume(int v) {
        if (chunk) chunk->volume = v;
    }

    void update(float dt) {}
    void rhythmUpdate() {}
    void render(Common::Layer layer) const {}

  private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel = 0;
    mutable bool played;
};

#endif  // SOUND_H
