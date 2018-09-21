#include "StageState.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <stdio.h>
#include "Alan.h"
#include "AlanActionControl.h"
#include "AlanAnimation.h"
#include "AlanItemCount.h"
#include "BigAlan.h"
#include "Camera.h"
#include "EnemySpawn.h"
#include "Game.h"
#include "HudCounter.h"
#include "HudMeter.h"
#include "HudTimer.h"
#include "Interpol.h"
#include "Light.h"
#include "MiniTileMap.h"
#include "Parallax.h"
#include "Sound.h"
#include "Sprite.h"
#include "Vec2.h"

StageState::StageState() {}

int StageState::count = 0;
int StageState::time_rhythm = 0; 
bool StageState::beat = false;

void StageState::no_effect(void *udata, Uint8 *stream, int len) { 
    static constexpr float bit_p_beat = 44100 * (120 / 60); 
    static constexpr float half_bit_p_beat = bit_p_beat / 2; 

    count += len;
    if (count >= half_bit_p_beat) { 
        beat = true;
        count -= half_bit_p_beat; 
        time_rhythm = SDL_GetTicks(); 
    }
}

void StageState::load_assets() { 
    Camera::offset.set(-(Camera::screen_size.x - 812), 0); 
    input.title = false; 

    // BG
    GameObject *back_g = new GameObject(Common::Layer::BG);
    back_g->world_reference = false; 
    object_array.emplace_back(back_g); 
    back_g->add_component(new bgCircularY(*back_g, "assets/img/bg1.png")); 
    back_g->add_component(new ParallaxY(*back_g, 0.1)); 
    back_g->box.pos = {212, 0}; 

    back_g = new GameObject(Common::Layer::BG); 
    back_g->world_reference = false; 
    object_array.emplace_back(back_g); 
    back_g->add_component(new bgCircularY(*back_g, "assets/img/bg2.png")); 
    back_g->add_component(new ParallaxY(*back_g, 0.3)); 
    back_g->box.pos = {212, 0}; 

    back_g = new GameObject(Common::Layer::BG); 
    back_g->world_reference = false; 
    object_array.emplace_back(back_g); 
    back_g->add_component(new bgCircularY(*back_g, "assets/img/bg3.png")); 
    back_g->add_component(new ParallaxY(*back_g, 0.5)); 
    back_g->box.pos = {212, 0}; 

    back_g = new GameObject(Common::Layer::BG); 
    back_g->world_reference = false; 
    object_array.emplace_back(back_g); 
    back_g->add_component(new bgCircularY(*back_g, "assets/img/bg4.png")); 
    back_g->add_component(new ParallaxY(*back_g, 0.7)); 
    back_g->box.pos = {212, 0}; 

    back_g = new GameObject(); 
    back_g->world_reference = false; 
    object_array.emplace_back(back_g); 
    back_g->add_component(new bgCircularY(*back_g, "assets/img/bg5.png")); 
    back_g->add_component(new ParallaxY(*back_g, 0.9)); 
    back_g->box.pos = {212, 0}; 

    // TileMap
    GameObject *gm =
        new GameObject(Common::Layer::DEFAULT | Common::Layer::LIGHT);
    object_array.emplace_back(gm); 
    tile_map = new TileMap(*gm, "assets/map/manager.json", true); 
    gm->add_component(tile_map); 

    Game::get_instance()->get_grid_control()->set_tile_map(tile_map); 

    // Alan
    GameObject *alan_go = new GameObject(); 
    Vec2 gp(3, 0);
    alan_go->box.x = (gp.x * GetGridSize()) - GetGridSize() / 2; 
    alan_go->box.y = (gp.y * GetGridSize()) - GetGridSize() / 2; 
    alan_go->gridPosition = gp; 
    object_array.emplace_back(alan_go); 

    Game::get_instance()->get_grid_control()->set_alan(get_object_ptr(alan_go)); 

    alan_go->add_component( 
        new Sprite(*alan_go, "assets/img/alan/idle.png", 2, 0.2)); 
    alan_go->add_component(new Sound(*alan_go)); 

    Alan *lil_alan = new Alan(*alan_go); 
    alan_go->add_component(lil_alan); 
 
    alan_go->add_component(new Interpol(*alan_go)); 
    alan_go->add_component(new AlanAnimation(*alan_go)); 
    alan_go->add_component(new AlanActionControl(*alan_go, get_grid_size())); 

    GameObject *alan_l = new GameObject(Common::Layer::LIGHT); 
    object_array.emplace_back(alan_l); 
    alan_l->add_component(new Light(*alan_l, GetObjectPrt(alan_go))); 

    Camera::follow(alan_go); 

    GameObject *es_go = new GameObject(); 
    es_go->add_component(new EnemySpawn(*es_go, tile_map)); 
    object_array.emplace_back(es_go); 

    GameObject *frame_g = new GameObject(Common::Layer::HUD); 
    frame_g->world_reference = false;
    object_array.emplace_back(frame_g);
    frame_g->add_component(new bgCircularY(*frame_g, "assets/img/framebg.png"));
    frame_g->add_component(new ParallaxY(*frame_g, 1));
    frame_g->box.pos = {0, 0};

    // MiniMap
    GameObject *mini_map_tile = new GameObject(Common::Layer::HUD);
    mini_map_tile->world_reference = false;
    mini_map_tile->box.pos = {30, 180};
    mini_map_tile->add_component(
        new Sprite(*mini_map_tile, "assets/img/bgminimap.png"));
    object_array.emplace_back(mini_map_tile);

    mini_map_tile = new GameObject(Common::Layer::HUD);
    mini_map_tile->box.pos = {60, 195};
    TileSet *mini_tile_set = new TileSet("assets/map/miniground.json");
    MiniTileMap *mini_tile_map = new MiniTileMap(*mini_map_tile, mini_tile_set,
                                               tile_map, get_object_prt(alan_go));
    mini_map_tile->add_component(mini_tile_map);
    object_array.emplace_back(mini_map_tile);

    // Big-Alan
    GameObject *big_alan = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(big_alan);
    big_alan->add_component(new Sprite(*big_alan, "assets/img/mooda.png", 2, -1));
    big_alan->add_component(new BigAlan(*big_alan));
    big_alan->world_reference = false;
    big_alan->box.pos = {0, Camera::screen_size.y - big_alan->box.h};

    // HUD
    GameObject *timer_hud = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(timer_hud);
    timer_hud->world_reference = false;
    timer_hud->box.pos = {212 + 600 / 2, Camera::screen_size.y - 50};
    timer_hud->add_component(new HudTimer(*timer_hud));

    GameObject *meter_heart = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(meter_heart);
    meter_heart->world_reference = false;
    meter_heart->box.pos = {30, 30};
    meter_heart->add_component(new HeartMeter(
        *meter_heart, "assets/hud/barravida.png", "assets/hud/coracao.png"));
    meter_heart->get_component<HeartMeter *>()->set_is_heart(true);
    meter_heart->get_component<HeartMeter *>()->set_alan(get_object_prt(alan_go));

    GameObject *meter_light = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(meter_light);
    meter_light->world_reference = false;
    meter_light->box.pos = {30, 100};
    meter_light->add_component(new LightMeter(
        *meter_light, "assets/hud/barraluz.png", "assets/hud/raio.png"));
    meter_light->get_component<LightMeter *>()->set_is_heart(false);
    meter_light->get_component<LightMeter *>()->set_alan(get_object_prt(alan_go));

    GameObject *counter_metal = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(counter_metal);
    counter_metal->world_reference = false;
    counter_metal->box.pos = {850, 10};
    counter_metal->add_component(new HudCounter(
        *counter_metal, "assets/hud/item1.png", "assets/hud/metali.png"));

    GameObject *counter_cristal = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(counter_cristal);
    counter_cristal->world_reference = false;
    counter_cristal->box.pos = {850, 160};
    counter_cristal->add_component(new HudCounter(
        *counter_cristal, "assets/hud/item2.png", "assets/hud/cristali.png"));

    GameObject *conter_petro = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(conter_petro);
    conter_petro->world_reference = false;
    conter_petro->box.pos = {850, 310};
    conter_petro->add_component(new HudCounter(
        *conter_petro, "assets/hud/item3.png", "assets/hud/petroleoi.png"));

    GameObject *item_count = new GameObject(Common::Layer::HUD);
    object_array.emplace_back(item_count);
    item_count->world_reference = false;
    item_count->add_component(new AlanItemCount(*item_count));
    lil_alan->set_item_count(item_count);

    // Music
    music.open("assets/audio/marmota.ogg");
    count = 0;
    half_beat_counter = 0;
    Mix_SetPostMix(no_effect, NULL);
}

void StageState::start() {
    if (!started) load_assets();

    start_array();
}

void StageState::update(float dt) {
    Camera::update(dt);

    if (beat) {
        beat = false;
        static constexpr float bpm = 120;
        static const int beat_time = (60 * 1000) / bpm;
        static const int half_beat_time = beat_time / 2;

        if (half_beat_counter == 0) Game::get_instance()->start_beat_time();

        Game::get_instance()->update_beat_time(half_beat_counter * half_beat_time);
        half_beat_counter++;
    }
    update_array(dt);
}

void StageState::rhythm_update() {
    if (!music_playing) {
        music.play();
        music_playing = true;
    }
    rhythm_update_array();
}

void StageState::rhythm_reset() { rhythm_reset_array(); }

void StageState::render() const { render_array(); }
