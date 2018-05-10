#include "Collider.h"
#include "Camera.h"
#include "Game.h"

void Collider::Update(float dt) {
    box = associated.box;
    box.size *= scale;
    box.SetCenter(associated.box.Center() + offset.Rotate(associated.angleDeg));
}

void Collider::Render() const {
#ifdef DEBUG
    Vec2 center(box.Center());
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg) +
                 center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).Rotate(associated.angleDeg) +
            center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center)
                .Rotate(associated.angleDeg) +
            center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).Rotate(associated.angleDeg) +
            center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
#endif  // DEBUG
}
