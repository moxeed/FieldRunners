#include "Tesla.hpp"
#include "../Source/Enemy.hpp"
#include "../Source/World.hpp"

#include<sstream>

#define IMAGE_MARGIN 15

Tesla::Tesla(Point position,World* world) : Tower(position,world)
{
    cool_down = TESLA_COOLDOWN;
    cost = TESLA_COOLDOWN ;
    upgrade_cost = TESLA_UPGRADECOST;
    damage = TESLA_DAMAGE;
    upgrade_damage_increase = TESLA_UPGRADE_DAMAGE_INCREASE;

    GameObject::position.y -= IMAGE_MARGIN;
    direction = - TowerDirection::DEG90;
}

void Tesla::attack()
{
    target->take_damage(damage);
}

Window& Tesla::operator>> (Window& window)
{
    std::stringstream stream;
    stream <<  "Assets/tesla/tesla" << level << "/" ;
    if(attack_mode > 0)
    {
        stream << 2;
        attack_mode --;
    }   
    else
        stream << 1;

    stream << ".png";

    window.draw_img(stream.str(),
        Rectangle(position - Point(1,1) * world->get_object_size() / 2, 
        position + Point(1,1) * world->get_object_size() / 2));
    
    return window;
}