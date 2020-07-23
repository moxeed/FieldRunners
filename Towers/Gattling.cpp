#include "Gattling.hpp"
#include "../Source/Enemy.hpp"
#include "../Source/World.hpp"

#include<sstream>

Gattling::Gattling(Point position,World* world) : Tower(position,world)
{
    cool_down = GATTLING_COOLDOWN;
    cost = GATTLING_COST ;
    upgrade_cost = GATTLING_UPGRADECOST;
    damage = GATTLING_DAMAGE;
    upgrade_damage_increase = GATTLING_UPGRADE_DAMAGE_INCREASE;
    direction = - TowerDirection::DEG90;
}

void Gattling::attack()
{
    if(!target->enemy_type == ENEMY_TYPE::ICERUNNER)
        target->take_damage(damage);    
}

Window& Gattling::operator>> (Window& window)
{
    std::stringstream stream;
    stream <<  "Assets/gattling/Gatling" << level;
    if(attack_mode > 0)
    {
        stream << "/shoot";
        attack_mode --;
    }   
    stream << "/" << abs(direction) + 1 << ".png";
    

    window.draw_img(stream.str(),
        Rectangle(position - Point(1,1) * world->get_object_size() / 2, 
        position + Point(1,1) * world->get_object_size() / 2) , NULL_RECT,0,direction < 0);
    
    return window;
}