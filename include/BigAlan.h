/**
 * @brief 
 * 
 * @file BigAlan.h
 * @brief creation of methods and attributes for character animation bigAlan
 */
#ifndef BIGALAN_H
#define BIGALAN_H
#include "Component.h"
#include "Sprite.h"
/**
 * @brief the class must be called to make the changes related to the main character
 * 
 */
class BigAlan : public Component {
  public:
    enum BAState { TRASH = 0, DECENT, GOOD, STARTER, MAXSTATE }; // constants to receive the images of the character

    explicit BigAlan(GameObject &associated) : Component(associated) {
      /**
       * @brief each constant is associated with an image to
       * generate the animation of the character
       * 
       */
        sprite = associated.GetComponent<Sprite *>();
        state[BAState::STARTER] = {"assets/img/mooda.png", 2, 2, -1};
        state[BAState::GOOD] = {"assets/img/mooda.png", 2, 2, -1};
        state[BAState::DECENT] = {"assets/img/mood2.png", 1, 1, 1};
        state[BAState::TRASH] = {"assets/img/mood3.png", 1, 1, 1};
    }
    /**
     * @brief method that will be called to update the character
     * 
     * @param dt 
     */
    void update(float dt);

    void rhythmUpdate()
    {
        associated.box.y += offset;
        offset = -offset;
    }
    
    void render(Common::Layer layer) const {}

  private:
  /**
   * @brief Variables combos that will make the calculations 
   * to define the animation of the character 
   * 
   */
    Sprite::SpriteState state[BAState::MAXSTATE];
    BAState current_state = BAState::STARTER;
    int offset = 0, old_combo = 0;
    Sprite *sprite;
};
/**
 * @brief class responsible for character state animation
 * 
 */
class SpriteState {
  public:
    std::string file;
    int frame_count;
    int total_frame_count;
    float frame_time;
};
#endif  // BIGALAN_H