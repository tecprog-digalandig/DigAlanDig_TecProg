#ifndef STATE_H
#define STATE_H
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "TileMap.h"
#include "TileSet.h"

class State {
  public:
    State();
    virtual ~State() {
        music.stop(); 
        object_array.clear(); 
    }

    virtual void load_assets() = 0; 
    virtual void update(float dt) = 0; 
    virtual void rhythm_update() = 0; 
    virtual void rhythm_reset() {} 
    virtual void render() const = 0; 

    virtual void start() = 0; 
    virtual void pause() = 0; 
    virtual void resume() = 0; 

    void update_array(float dt); 
    void rhythm_update_array(); 
    void rhythm_reset_array(); 
    void start_array(); 
    void render_array() const; 

    virtual std::weak_ptr<GameObject> add_object(GameObject* go); 
    virtual std::weak_ptr<GameObject> get_object_ptr(GameObject* go); 

    bool pop_requested() const { return pop_requested; } 
    bool quit_requested() const { return quit_requested; } 

    TileMap* tile_map = nullptr; 

    Music* get_music() { return &music; } 

    void stop_music() { music_playing = false; } 

    int get_grid_size() const { return grid_size; } 

  protected:
    const int grid_size = 100; 

    bool pop_requested = false; 
    bool quit_requested = false; 
    bool started = false; 

    std::vector<std::shared_ptr<GameObject>> object_array; 

    InputManager& input;
    Music music;
    bool music_playing = false; 
    TileSet* tile_set = nullptr; 

  private:
    void render_light() const; 
};

#endif
