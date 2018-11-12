#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    Timer() {}
    void update(float delta_time) 
    { 
        time += delta_time; 
    }

    void restart() 
    { 
        time = 0; 
    }
    float get() const 
    { 
        return time; 
    }

  private:
    float time = 0;
};

#endif 
