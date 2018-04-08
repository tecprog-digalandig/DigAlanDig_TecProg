#ifndef SOUND_H
#define SOUND_H
#include "Component.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <typeinfo>

class Sound : public Component {
  public:
    Sound(GameObject& associated) : Component(associated), chunk(nullptr) {}
    Sound(GameObject& associated, std::string file)
        : Component(associated), chunk(nullptr) {
        Sound::Open(file);
    }

    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen(void) { return (bool)chunk; }

    void Update(float dt){}
    void Render(){}
    bool Is(std::string type) {
        std::cout << type << std::endl;
        std::cout << typeid(*this).name() << std::endl;
        return !type.compare(typeid(*this).name());
    }

  private:
    Mix_Chunk* chunk;
    int channel;
};

#endif  // SOUND_H
