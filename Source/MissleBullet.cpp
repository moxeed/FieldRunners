#include "MissleBullet.hpp"
#include "../../Source/World.hpp"

#include <iostream>

using namespace std;

MissleBullet::MissleBullet(int _damage,Point position ,Enemy* enemy ,World* world)
    : Bullet(250, position, world)
{    
    target = enemy;
    damage = _damage; 
}

void MissleBullet::do_damage()
{
    world->do_areal_damage(position,range,damage);
}