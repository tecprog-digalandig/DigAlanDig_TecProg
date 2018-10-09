#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "Vec2.h"

class Camera {
  public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    static Vec2 Center();
    static void Shake(int intensity = 4, float duration = 0.1);
    /* static void SetNewCameraPos(Vec2 newPos) { pos = newPos; } */

    static void RhythmUpdate();

    static Vec2 pos, speed, screenSize, offset;

    enum Movement { ATTACHED = 1, CONSTSCROLL, FRIENDLYSCROLL, NONE };
    static Movement current_move;

  private:
    static GameObject* focus;
    static Vec2 shake;
    static int shake_intensity;
    static float shake_duration;
};

#endif  // CAMERA_H
