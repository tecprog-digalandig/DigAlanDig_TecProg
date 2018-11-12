#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "Vec2.h"

class Camera {
  public:
    static void follow(GameObject* newFocus);
    static void unfollow();
    static void update(float delta_time);
    static Vec2 center();
    static void shakeFunc(int intensity = 4, float duration = 0.1);
    /* static void SetNewCameraPos(Vec2 newPos) { pos = newPos; } */

    static void rhythmUpdate();

    static Vec2 pos, speed, screen_size, off_set;

    enum movement { ATTACHED = 1, CONSTSCROLL, FRIENDLYSCROLL, NONE };
    static movement current_move;

  private:
    static GameObject* focus;
    static Vec2 shake;
    static int shake_intensity;
    static float shake_duration;
};

#endif  // CAMERA_H