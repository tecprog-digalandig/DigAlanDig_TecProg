#include "Sprite.h"
#include "Alan.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

<<<<<<< HEAD
void Sprite::Open(const std::string &file) {
    texture = Resources::getImage(file);

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    width /= frameCount;
    frameTimeTotal = frameTime;
    setFrame(0);
    associated.box.size.Set(width, height);
    timeElapsed = 0;
}

void Sprite::Open(SpriteState sstate, int dir) {
    texture = Resources::getImage(sstate.file);
=======
void Sprite::open(const std::string &file) { 
    texture = Resources::get_image(file); 

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height); 
    width /= frame_count; 
    frame_time_total = frame_time; 
    set_frame(0); 
    associated.box.size.set(width, height); 
    time_elapsed = 0; 
}

void Sprite::open(SpriteState sstate, int dir) { 
    texture = Resources::get_image(sstate.file); 
>>>>>>> 702c55cc40968618a3571eb2f9a2b3d2471736e4

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height); 
    width /= sstate.total_frame_count; 
    frame_count = sstate.frame_count; 
    init_frame = dir * sstate.frame_count; 

<<<<<<< HEAD
    setFrame(initFrame);
    frameTimeTotal = sstate.frameTime * sstate.frameCount;
    frameTime = sstate.frameTime;
    associated.box.size.Set(width, height);
    timeElapsed = 0;
=======
    set_frame(init_frame); 
    frame_time_total = sstate.frame_time * sstate.frame_count; 
    frame_time = sstate.frame_time; 
    associated.box.size.set(width, height); 
    time_elapsed = 0; 
>>>>>>> 702c55cc40968618a3571eb2f9a2b3d2471736e4
}

void Sprite::set_scale_x(double scale_x, double scale_y) { 
    scale.x = scale_x ? scale_x : scale.x; 
    scale.y = scale_y ? scale_y : scale.y; 
}

<<<<<<< HEAD
void Sprite::setFrame(int frame) {
    currentFrame = frame;
=======
void Sprite::set_frame(int frame) { 
    current_frame = frame; 
>>>>>>> 702c55cc40968618a3571eb2f9a2b3d2471736e4
    Vec2 size(width, height);
    Vec2 pos(width * (current_frame), 0); 
    clip_rect = rect(pos, size); 
}

<<<<<<< HEAD
<<<<<<< HEAD
void Sprite::render(Common::Layer layer) const {
    if (isOpen()) {
        Vec2 offset;
        if (associated.world_reference) offset = Camera::pos;
=======
void Sprite::render(Common::Layer layer) const { 
    if (is_open()) { 
        Vec2 offset;
        if (associated.world_reference) offset = Camera::pos; 
>>>>>>> 702c55cc40968618a3571eb2f9a2b3d2471736e4
=======
void Sprite::render(Common::Layer layer) const {
    if (IsOpen()) {
        Vec2 offset;
        if (associated.world_reference) offset = Camera::pos;
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
        Rect dst(associated.box.pos - offset, {(double)width, (double)height});

        if (scale.x != 1 || scale.y != 1) dst.Scale(scale);

<<<<<<< HEAD
        SDL_Rect dstRect = dst;
        SDL_RenderCopyEx(Game::getInstance()->GetRenderer(), texture.get(),
                         &clipRect, &dstRect, associated.angleDeg, nullptr,
=======
        SDL_Rect dst_rect = dst; 
        SDL_RenderCopyEx(Game::get_instance()->get_renderer(), texture.get(), 
                         &clip_rect, &dst_rect, associated.angle_deg, nullptr, 
>>>>>>> 702c55cc40968618a3571eb2f9a2b3d2471736e4
                         SDL_FLIP_NONE);
    }
}

<<<<<<< HEAD
void Sprite::update(float dt) { 
    time_elapsed += dt; 

    self_destruct_count.update(dt); 
    if (seconds_to_self_destruct > 0 && 
        self_destruct_count.get() > seconds_to_self_destruct) { 
        associated.request_delete(); 
=======
void Sprite::update(float dt) {
    timeElapsed += dt;

    selfDestructCount.update(dt);
    if (secondsToSelfDestruct > 0 &&
        selfDestructCount.Get() > secondsToSelfDestruct) {
        associated.RequestDelete();
>>>>>>> 26ad0751d659fc099e9afdd63220ee4bd9fe09f9
        return;
    }

    if (associated.get_component<Alan *>() != nullptr) { 
        alan_update(dt); 
        return;
    } else {
        if (frame_time > 0 && ((current_frame + 1) * frame_time <= time_elapsed)) { 
            int new_frame = floor(time_elapsed / frame_time); 
            set_frame(new_frame % frame_count); 
        }
    }
}

void Sprite::alan_update(float dt) { 
    if (frame_time > 0) { 
        if (time_elapsed - (frame_time * (current_frame - init_frame)) >= 
            frame_time) { 
            if ((current_frame - init_frame) < (frame_count - 1)) { 
                set_frame(current_frame + 1); 

            } else {
                set_frame(init_frame); 
            }
        }
    } else if (frame_time != -1) { 
        if (time_elapsed - (std::abs(frame_time) * (current_frame - init_frame)) >= 
            std::abs(frame_time)) { 
            if ((current_frame - init_frame) < (frame_count - 1)) 
                set_frame(current_frame + 1); 
        }
    }
}
