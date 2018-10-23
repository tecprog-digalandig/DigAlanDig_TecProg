#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "Vec2.h"

class Camera {
  public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float delta_time);
    static Vec2 Center();
    static void shakefunc(int intensity = 4, float duration = 0.1);
    /* static void SetNewCameraPos(Vec2 newPos) { pos = newPos; } */

    static void rhythmUpdate();

    static Vec2 pos, speed, screenSize, offset;

    enum Movement { ATTACHED = 1, CONSTSCROLL, FRIENDLYSCROLL, NONE };
    static Movement currentMove;

  private:
    static GameObject* focus;
    static Vec2 shake;
    static int shakeIntensity;
    static float shakeDuration;
};

#endif  // CAMERA_H
