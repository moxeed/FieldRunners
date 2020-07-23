#include "Glue.hpp"
#include "../Source/Enemy.hpp"
#include "../Source/World.hpp"
#include "Bullets/GlueBullet.hpp"

#include<sstream>

Glue::Glue(Point position,World* world) : Tower(position,world)
{
    cool_down = GLUE_COOLDOWN;
    cost = GLUE_COST ;
    upgrade_cost = GLUE_UPGRADECOST;
    damage = GLUE_DAMAGE;
    upgrade_damage_increase = GLUE_UPGRADE_DAMAGE_INCREASE;
    slow_down_duration = SLOWDOWN_DURATION;
    direction = - TowerDirection::DEG90;
}

void Glue::attack()
{
    if(!target->enemy_type == ENEMY_TYPE::ICERUNNER)
        world->add_object(new GlueBullet(damage, slow_down_duration, position, target, world));
    set_tagret();
}

Window& Glue::operator>> (Window& window)
{
    std::stringstream stream;
    
    stream <<  "Assets/goo/glue" << level <<"/" << abs(direction) + 1 << ".png";

    window.draw_img(stream.str(),
        Rectangle(position - Point(1,1) * world->get_object_size() / 2, 
        position + Point(1,1) * world->get_object_size() / 2) , NULL_RECT,0,direction < 0);
    
    return window;
}

void Glue::custom_level_up()
{
    slow_down_duration += slow_down_upgrade;
}
