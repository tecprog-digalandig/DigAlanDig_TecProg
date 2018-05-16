#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    Timer() {}
    void Update(float dt) { time += dt; }
    void Restart() { time = 0; }
    float Get() const { return time; }

  private:
    float time = 0;
};

#endif  // TIMER_H
