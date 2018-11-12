#include "Sprite.h"
#include "Alan.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

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

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height); 
    width /= sstate.total_frame_count; 
    frame_count = sstate.frame_count; 
    init_frame = dir * sstate.frame_count; 

    setFrame(initFrame);
    frameTimeTotal = sstate.frameTime * sstate.frameCount;
    frameTime = sstate.frameTime;
    associated.box.size.Set(width, height);
    timeElapsed = 0;
}

void Sprite::set_scale_x(double scale_x, double scale_y) { 
    scale.x = scale_x ? scale_x : scale.x; 
    scale.y = scale_y ? scale_y : scale.y; 
}

void Sprite::setFrame(int frame) {
    currentFrame = frame;
    Vec2 size(width, height);
    Vec2 pos(width * (current_frame), 0); 
    clip_rect = rect(pos, size); 
}

void Sprite::render(Common::Layer layer) const { 
    if (is_open()) { 
        Vec2 offset;
        if (associated.world_reference) offset = Camera::pos; 
        Rect dst(associated.box.pos - offset, {(double)width, (double)height});

        if (scale.x != 1 || scale.y != 1) dst.Scale(scale);

        SDL_Rect dstRect = dst;
        SDL_RenderCopyEx(Game::getInstance()->GetRenderer(), texture.get(),
                         &clipRect, &dstRect, associated.angleDeg, nullptr,
                         SDL_FLIP_NONE);
    }
}

void Sprite::update(float dt) { 
    time_elapsed += dt; 

    self_destruct_count.update(dt); 
    if (seconds_to_self_destruct > 0 && 
        self_destruct_count.get() > seconds_to_self_destruct) { 
        associated.request_delete(); 
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
