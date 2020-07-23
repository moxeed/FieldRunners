#include <chrono>
#include "../RSDL/rsdl.hpp"

#ifndef ROUNDE_HEADER
#define ROUNDE_HEADER

class World;
class Enemy;

#define SPAWN_DELAY 0.5

class Round
{
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::duration<float> time_span;

private:
    int runner_count;
    int icerunner_count;
    int heavy_count;
    int bike_count;

    World* world;
    std::chrono::steady_clock::time_point last_spawn;

    Point enemy_start_pos;

    bool is_spawn_time();
    Enemy* get_next_random_enemy();

public:
    Round(int _runner_count, int _icerunner_count, int _heavy_count, int _bike_count 
        ,World * world);
    bool update();
};

#endif