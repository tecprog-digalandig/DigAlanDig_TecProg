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

    virtual void loadAssets() = 0;
    virtual void update(float delta_time) = 0;
    virtual void rhythmUpdate() = 0;
    virtual void rhythmReset() {}
    virtual void render() const = 0;

    virtual void start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    void UpdateArray(float delta_time);
    void rhythmUpdateArray();
    void RhythmResetArray();
    void StartArray();
    void RenderArray() const;

    virtual std::weak_ptr<GameObject> add_object(GameObject* go); 
    virtual std::weak_ptr<GameObject> get_object_ptr(GameObject* go); 

    bool PopRequested() const { 
      return pop_requested; 
      }
    bool QuitRequested() const { 
      return quit_requested; 
      }

    TileMap* tile_map = nullptr; 

    Music* getMusic() { 
      return &music; 
      }

    void StopMusic() { 
      music_playing = false; 
      }

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
