#include "Missle.hpp"
#include "../Source/Enemy.hpp"
#include "../Source/World.hpp"
#include "Bullets/MissleBullet.hpp"

#include<sstream>

Missle::Missle(Point position,World* world) : Tower(position,world)
{
    cool_down = MISSLE_COOLDOWN;
    cost = MISSLE_COST;
    upgrade_cost = MISSLE_UPGRADECOST;
    damage = MISSLE_DAMAGE;
    upgrade_damage_increase = MISSLE_UPGRADE_DAMAGE_INCREASE;
    direction = - TowerDirection::DEG90;
}

void Missle::attack()
{
    world->add_object(new MissleBullet(damage ,position ,target ,world ));
}

Window& Missle::operator>> (Window& window)
{
    std::stringstream stream;
    
    stream <<  "Assets/missle/missle" << level <<"/" << abs(direction) + 1 << ".png";

    window.draw_img(stream.str(),
        Rectangle(position - Point(1,1) * world->get_object_size() / 2, 
        position + Point(1,1) * world->get_object_size() / 2) , NULL_RECT,0,direction < 0);
    
    return window;
}