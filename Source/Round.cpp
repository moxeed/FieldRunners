#include "Round.hpp"
#include "World.hpp"

#include "../Enemies/Bike.hpp"
#include "../Enemies/Heavy.hpp"
#include "../Enemies/Runner.hpp"
#include "../Enemies/IceRunner.hpp"

#include <random>
#include <iostream>

using namespace std;

bool Round::is_spawn_time()
{
    auto current_time = clock::now();
    time_span passed_time = chrono::duration_cast<time_span>(current_time - last_spawn);

    if(passed_time.count() >= SPAWN_DELAY)
    {   
        last_spawn = current_time;
        return true;
    }

    return false;
}
Enemy* Round::get_next_random_enemy()
{
    int random_num = rand() % 4;

    while (true)
    {
        switch (random_num)
        {
        case RUNNER:
            if(runner_count > 0)
            {
                runner_count --;
                return new Runner(enemy_start_pos,Directions::right,world);
            }
            break;
        case ICERUNNER:
            if(icerunner_count > 0)
            {
                icerunner_count --;
                return new IceRunner(enemy_start_pos,Directions::right,world);
            }
            break;
        case HEAVY:
            if(heavy_count > 0)
            {
                heavy_count--;
                return new Heavy(enemy_start_pos,Directions::right,world);
            }
            break;
        case BIKE:
            if(bike_count > 0)
            {
                bike_count --;
                return new Bike(enemy_start_pos,Directions::right,world);
            }
            break;
        }

        random_num ++;
        random_num %= 4;
    }
}

Round::Round(int _runner_count, int _icerunner_count, int _heavy_count, int _bike_count 
    ,World * world) :  world(world)
{
    bike_count =_bike_count;
    heavy_count = _heavy_count;
    runner_count = _runner_count;
    icerunner_count = _icerunner_count;
    enemy_start_pos = world->origin + world->get_tile_size() * world->assets.enemy_route->next->value;

    srand(time(NULL));
}

bool Round::update()
{
    if( icerunner_count + bike_count +
        runner_count   + heavy_count <= 0 )
        return false;
    if(is_spawn_time())
    {
        auto enemy = get_next_random_enemy();
        world->add_enemy(enemy);
    }
    return true;
}