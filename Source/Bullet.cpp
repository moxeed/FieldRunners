#include "Bullet.hpp"
#include "Enemy.hpp"
#include "World.hpp"

#include<iostream>

using namespace std;

Bullet::Bullet(int _speed, Point position, World* world ,string animation_name) : 
    GameObject(position,world)
{
    speed = _speed;
    animation = world->assets.get_anmation(animation_name);    
}

bool Bullet::is_reached()
{
    return position.distance(target->get_position()) <= 30 * ERROR;
}

bool Bullet::is_delete_time()
{
    return is_reached();
}

Window& Bullet::operator>>(Window& window)
{
    window.draw_img(animation.get_current_frame_name(),Rectangle(position - Point(size/2 , size/2), 
            position + Point(size/2 , size/2)), NULL_RECT, 90 + position.angle_to(target->position) / M_PI * 180);

    return window;
}

void Bullet::update()
{
    if(is_reached())
    {
        do_damage();
    }

    double angle = position.angle_to(target->get_position());

    position.x += speed * cos(angle) / world->get_game_time_convertion_rate();
    position.y += speed * sin(angle) / world->get_game_time_convertion_rate();
}