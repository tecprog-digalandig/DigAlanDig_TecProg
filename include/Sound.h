#ifndef SOUND_H
#define SOUND_H
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"
#include "Resources.h"

class Sound : public Component 
{
  public:
    explicit Sound(GameObject& associated)
        : Component(associated), chunk(nullptr), played(false) {}
    Sound(GameObject& associated, const std::string& file, bool play = false)
        : Component(associated), chunk(nullptr), played(false) 
        {
        Open(file);
        if (play) play_func();
    }

    ~Sound() { stop(); 
    }

    void Open(const std::string& file) 
    { 
        chunk = Resources::getSound(file); 
    }

    bool isOpen() const 
    { 
        return (bool)chunk; 
    }

    bool canEnd() const 
    { 
        return played; //&& !mixPlaying(channel); 
    }

    void play_func(int times = 1);

    void stop() const 
    {
        //if (chunk) mixHaltChannel(int channel);
    }

    void setVolume(int v) 
    {
        if (chunk) chunk->volume = v;
    }

    void update(float delta_time) {}
    void rhythmUpdate() {}
    void mixHaltChannel(int channel){}
    void render(Common::Layer layer) const {}

  private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel = 0;
    mutable bool played;
};

#endif  // SOUND_H
