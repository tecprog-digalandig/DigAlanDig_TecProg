#ifndef SPRITE_H
#define SPRITE_H
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Component.h"
#include "Timer.h"

class Sprite : public Component {
  public:
    class SpriteState {
      public:
        std::string file;
        int frame_count; 
        int total_frame_count; 
        float frame_time; 
    };

    explicit Sprite(GameObject& associated)
        : Component(associated), scale(1, 1) {}

    Sprite(GameObject& associated, const std::string& file, int frame_count = 1,
           float frame_time = 1, float seconds_to_self_destruct = 0)
        : Component(associated),
          frame_count(frame_count), 
          frame_time(frame_time), 
          seconds_to_self_destruct(seconds_to_self_destruct), 
          scale(1, 1) {
        Sprite::open(file); 
    }
    ~Sprite() {}

    void open(const std::string& file); 
    void open(SpriteState sstate, int dir); 
    void set_clip(int x, int y, int w, int h) { clip_rect = {x, y, w, h}; } 
    int get_width() const { return width; } 
    int get_height() const { return height; } 
    bool is_open() const { return static_cast<bool>(Sprite::texture); } 

    void update(float dt); 
    void alan_update(float dt); 
    void rhythm_update() { 
        if (frame_time == -1) 
            set_frame(((current_frame - init_frame) + 1) % frame_count + init_frame); 
    }
    void rhythm_reset() {} 
    void render(Common::Layer layer) const; 

    void set_scale_x(double scale_x, double scale_y); 
    void set_scale_x(double s) { set_scale_x(s, s); } 
    void set_scale_x(const Vec2& v) { set_scale_x(v.x, v.y); } 
    Vec2 get_scale() const { return scale; } 

    void set_frame(int frame); 
    void set_frame_count(int frame_count) { this->frame_count = frame_count; } 
    void set_frame_time(float frame_time) { this->frame_time = frame_time; } 

    bool frame_time_passed() { 
        if (frame_time_total < 0) return false; 

        if (time_elapsed < frame_time_total) 
            return false;
        else {
            return true;
        }
    }

    void set_blend_mode(SDL_BlendMode mode) { 
        SDL_SetTextureBlendMode(texture.get(), mode); 
    }

    void set_color(int r, int g, int b) { 
        SDL_SetTextureColorMod(texture.get(), r, g, b); 
    }

    int get_frame_count() { return frame_count; } 

    void time_elapsed_reset() { time_elapsed = 0; } 

  private:
    std::shared_ptr<SDL_Texture> texture = nullptr;
    int width = 0;
    int height = 0;
    int frame_count = 1; 
    int init_frame = 0; 
    float frame_time = 1; 
    float frame_time_total = 1; 
    int current_frame = 0; 
    float time_elapsed = 0; 
    float seconds_to_self_destruct = 0;  
    Timer self_destruct_count; 

    SDL_Rect clip_rect; 
    Vec2 scale;
};

#endif
