#include "Round.hpp"
#include "Assets.hpp"

#include "Tower.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

#include<vector>
#include<list>

#ifndef WORLD_HEADER
#define WORLD_HEADER

#define ROUND_DEALY 3000
#define MSG_DEALY 500

class World
{
private:
    const int game_step = 40;
    static constexpr int screen_width = 1365;
    static constexpr int screen_heght = 1024;
    const int tile_size = 60;
    const int object_size = 80;

    Window window; 
    Point *last_click_pos = NULL;
    
    std::list<GameObject*> objects;
    std::list<Enemy*> enemies;
    std::list<Tower*> towers;
    std::list<Error*> errors;

    std::vector<Round> rounds;

    bool handle_events();
    void handle_key_press(char key);

    void read_round_data();
    void check_round();

    void update_enemies();
    void draw_enemies();

    void update_towers();
    void draw_towers();

    void update_objects(); 
    void draw_objects(); 

    void draw_hud(Point* select_pos);
    void draw_all();
    Point align_point(Point source);
    Point point_to_location(Point point);


public:
    int current_round = 0;
    
    Point origin;
    Assets assets;
    Player player;

    World();


    int update();
    float get_game_time_convertion_rate();
    int get_object_size();
    int get_tile_size();
    void add_enemy(Enemy* enemy);
    void add_object(GameObject* object);
    bool add_tower(Point* position, char type);
    void add_error(Error* error);

    void do_areal_damage(Point center, int radius, int damage);
    void do_areal_slow_down(Point center, int radius, int percent ,int slow_down_time);

    Enemy * find_closest_enemy(Point position);
    LinkedList<Point>* get_enemy_route_start();
};

#endif