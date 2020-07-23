#include "Enemy.hpp"
#include "GameObject.hpp"
#include "World.hpp"

#include<iostream>

#include<sstream>


using namespace std;

Enemy::Enemy(int _hit_point, int _speed, int _die_reward, int _reach_punish,
    Point pos, Direction direction, World* world, string prefix) 
            : GameObject(pos,world), direction(direction)
{
    hit_point = _hit_point  + _hit_point * world->current_round * 0.1;
    die_reward = _die_reward;
    animation_prefix  = prefix;
    reach_punish = _reach_punish;
    //exception
    destination = world->get_enemy_route_start()->next->next;
    defalut_speed = _speed / world->get_game_time_convertion_rate();
    speed = _speed / world->get_game_time_convertion_rate(); 
    set_animation();
}

bool Enemy::is_reached()
{
    Point distance = world->origin + destination->value * world->get_tile_size() - position;
    return abs(distance.x + distance.y) < ERROR;
}

bool Enemy::is_died()
{
    return hit_point <= 0;
}

void Enemy::success()
{
    speed = 0;
    hit_point = 0;
    world->player.loss_health(reach_punish);
}

Point Enemy::find_next_destination()
{
    destination = destination->next;
    return destination->value;
}

void Enemy::update()
{
    if(slow_down_time -- <= 0)
    {
        speed = defalut_speed;
    }
    if(is_reached())
    {
        LinkedList<Point>* next_destination = destination->next;

        if(next_destination == NULL)
        {
            success();
            return;
        }

        direction = Direction(next_destination -> value - destination -> value);
        destination = destination->next;
        set_animation();
    }
    position = direction * speed + position;
}
void Enemy::die()
{
    speed = 0;
    hit_point = 0;
    world ->player.take_reward(die_reward);
}

void Enemy::set_animation()
{
    current_animation = world->assets.get_anmation(animation_prefix+"run_"+direction.identifier);
}

void Enemy::take_damage(int value)
{
    hit_point -= value;
    if(is_died())
        die();
}
Point Enemy::get_position()
{
    return position;
}

void Enemy::slow_down(int percent,int time)
{
    speed = (float)(100 - percent) * defalut_speed / 100;
    slow_down_time = time / world->get_game_time_convertion_rate();
}

Window& Enemy::operator>> (Window& window)
{
    Point draw_position = position + Point(x_displace,y_displace);
    window.draw_img(current_animation.get_current_frame_name(),
            Rectangle(draw_position - Point(1,1) * size / 2 , 
                      draw_position + Point(1,1) * size / 2 ), NULL_RECT, 0, direction == Directions::left);

    window.draw_rect ( Rectangle(position + Point(-hit_point/8 ,-60) , position + Point(hit_point/8 ,-55)) ,RED , 5);
    return window;
}


Direction Directions::up = Direction(0,-1,"1");
Direction Directions::right = Direction(1,0,"2");
Direction Directions::down = Direction(0,1,"3");
Direction Directions::left = Direction(-1,0,"4");

Point Direction::operator + (Point pos)
{
    return Point(pos.x + x_scale, pos.y + y_scale);
}

Direction Direction::operator * (int speed)
{
    return Direction(x_scale * speed,y_scale * speed,identifier);
}

Direction::Direction(int _x_scale,int _y_scale,std::string _identifier)
{
    identifier = _identifier;
    x_scale = _x_scale;
    y_scale = _y_scale;
}

Direction::Direction(Point point)
{
    x_scale = point.x == 0 ? 0 : point.x < 0 ? -1 : 1;
    y_scale = point.y == 0 ? 0 : point.y < 0 ? -1 : 1;

    if(point.x != 0)
        identifier = point.x < 0 ? "4" : "2";
    if(point.y != 0)
        identifier = point.y < 0 ? "1" : "3";
}
bool Direction::operator == (Direction direction)
{
    return identifier == direction.identifier;
}
