#ifndef ENDSTATE_H
#define ENDSTATE_H
#include "State.h"

class EndState : public State {
  public:
    EndState();
    ~EndState() { delete music; }
    void LoadAssets();
    void Update(float dt);
    void Render() const;
    void Start();
    void Pause() {}
    void Resume() {}

  private:
    Music* music = nullptr;
};

#endif  // ENDSTATE_H
