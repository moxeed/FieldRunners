#include "Tower.hpp"
#include "Enemy.hpp"
#include "World.hpp"

#include <cmath>

using namespace std;

Tower::Tower(Point pos,World* world) : GameObject(pos,world)
{
    target = NULL;
}

void Tower::update()
{
    if(target == NULL)
    {
        set_tagret();
    }

    if(target != NULL)
    {  
        try
        {
            if(is_attack_time())
            {
                attack();
                attack_mode = ATTACK_MODE_DURATION;
            }

            if(target->is_died() || !is_enemy_in_range())
            {
                target = NULL;
            }
            set_direction();
        } 
        catch(exception e)
        {
            target = NULL;
        }
    }
}

bool Tower::is_attack_time()
{
    auto current_time = clock::now();
    time_span passed_time = chrono::duration_cast<time_span>(current_time - last_attack);
    
    if(passed_time.count() > cool_down)
    {
        last_attack = current_time;
        return true;
    }
    return false;
}

void Tower::set_direction()
{
    if(target == NULL)
        return;
    Point target_pos = target->get_position();

    if(target_pos.y == position.y)
        return;

    direction = atan2(target_pos.x - position.x , position.y - target_pos.y ) * 18 / 3.1415 + 0.5;
}

void Tower::set_tagret()
{
    target = world->find_closest_enemy(position);

    if(!is_enemy_in_range())
        target = NULL;
}

bool Tower::is_enemy_in_range()
{
    if(target == NULL)
        return false;

    return target-> position.distance(position) <= range * range;
}
void Tower::level_up()
{
    if(level == MAX_TOWER_LEVEL)
    {
        world->add_error(new Error(Error::max_level));
        return;
    }
    if(world->player.take_money(upgrade_cost))
    {
        custom_level_up();
        damage += upgrade_damage_increase;
        level++;
    }
    else
        world->add_error(new Error(Error::money_error));
    
}