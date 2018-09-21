#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    Timer() {}
    void update(float dt) { time += dt; } 
    void restart() { time = 0; } 
    float get() const { return time; } 

  private:
    float time = 0;
};

#endif 
