#include "World.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"

#include "../Towers/Gattling.hpp"
#include "../Towers/Missle.hpp"
#include "../Towers/Glue.hpp"
#include "../Towers/Tesla.hpp"

#include "../Enemies/Bike.hpp"
#include "../Enemies/Heavy.hpp"
#include "../Enemies/Runner.hpp"
#include "../Enemies/IceRunner.hpp"

#include "../Towers/Bullets/MissleBullet.hpp"

#include "Bullet.hpp"

#include<sstream>
#include<iostream>

using namespace std;


World::World() : window(screen_width,screen_heght,"FiledRunners") 
{
    origin = Point(120,175) + Point(tile_size/2,tile_size/2);
    window.play_music("Assets/theme.mp3");
    read_round_data();
}

int World::update()
{
    
    check_round();

    update_objects();
    update_towers();
    update_enemies();

    draw_all();

    window.update_screen();
    delay(game_step);

    return handle_events();
}

void World::update_towers()
{
    for (Tower* tower : towers)
        tower->update();
}

void World::update_enemies()
{
    for(auto enemy = enemies.cbegin(); enemy != enemies.cend();)
        if((*enemy)->is_died())
        {  
            delete *enemy;
            enemies.erase(enemy++);
        }
        else
        {
            (*enemy)->update();
            enemy ++;
        }
}

void World::draw_towers()
{
    for (Tower* tower : towers)
        *tower >> window;
}

void World::draw_enemies()
{
    for (auto enemy = enemies.rbegin(); enemy != enemies.rend() ; enemy++) 
        **enemy >> window;
}

void World::update_objects()
{
    for(auto object = objects.cbegin(); object != objects.cend();)
        if((*object)->is_delete_time())
        {  
            (*object)->update();
            delete *object;
            objects.erase(object++);
        }
        else
        {
            (*object)->update();
            object ++;
        }
}
void World::draw_objects()
{
    for(GameObject* object : objects)
        *object >> window;
}


void World::draw_hud(Point* select_pos)
{
    if(select_pos != NULL)
    {
        auto mouse_pos = align_point(*select_pos);
        window.draw_rect(Rectangle( mouse_pos - Point(tile_size/2,tile_size/2) ,
                                    mouse_pos + Point(tile_size/2,tile_size/2)));
    }
    
    window.draw_img("Assets/Heart.png",Rectangle(Point (10,10),Point (object_size +10,object_size +10)));
    window.draw_img("Assets/Coin.png",Rectangle(Point (1250,10),Point (object_size +1250,object_size +10)));

    player >> window;

    for(auto error = errors.cbegin(); error != errors.cend();)
    {
        if((*error)->is_delete_time())
        {  
            delete *error;
            errors.erase(error++);
        }
        else
        {
            **error >> window;
            error++;
        }
    }
}


float World::get_game_time_convertion_rate()
{
    return 500 / game_step;
}
int World::get_object_size()
{
    return object_size;
}

LinkedList<Point>* World::get_enemy_route_start()
{
    return assets.enemy_route;
}
Enemy * World::find_closest_enemy(Point position)
{
    int distance;
    Enemy * closet_enemy = NULL;

    for(Enemy*& enemy : enemies)
    {
        Point dis = enemy->get_position() - position;
        int current_distance = pow(dis.x,2) + pow(dis.y,2);

        if(current_distance < distance || closet_enemy == NULL)
        {
            distance = current_distance;
            closet_enemy = enemy;
        }
    }

    return closet_enemy;    
}
int World::get_tile_size()
{
    return tile_size;
}

void World::read_round_data()
{
    int runner_count ,icerunner_count ,
        heavy_count ,bike_count ;

    while (cin >> runner_count >> icerunner_count >> heavy_count >> bike_count)
    {
        rounds.push_back(Round(runner_count ,icerunner_count ,heavy_count ,bike_count ,this));
    }
    
}

void World::add_enemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void World::add_object(GameObject* object)
{
    objects.push_back(object);
}

void World::handle_key_press(char key)
{
    if(last_click_pos == NULL)
    {
        add_error(new Error(Error::no_choose));
        return;
    }
        
    if(key == 'U' || key == 'u')
    {   
        auto position = align_point(*last_click_pos);
        for(auto tower : towers)
            if(tower->position.x == position.x && tower->position.y == position.y)
            {
                tower->level_up();
                return;
            }
    }
    else
    {
        if(assets.get_tile_state(point_to_location(*last_click_pos)) == FULL)
        {
            add_error(new Error(Error::full_house));
            return;
        }
        if(add_tower(last_click_pos, key))
        {
            assets.set_tile_state(point_to_location(align_point(*last_click_pos)),FULL);
        }
    }
}

bool World::add_tower(Point* position,char type)
{
    auto deploay_position = align_point(*position);

    switch (type)
    {
    case 'g':
    case 'G':
        if(player.take_money(GATTLING_COST))
        {
            towers.push_back(new Gattling(deploay_position,this));
            return true;
        }
        break;
    
    case 'm':
    case 'M':
        if(player.take_money(MISSLE_COST))
        {
            towers.push_back(new Missle(deploay_position,this));
            return true;
        }
        break;
    
    case 't':
    case 'T':
        if(player.take_money(TESLA_COST))
        {
            towers.push_back(new Tesla(deploay_position,this));
            return true;
        }
        break;
    
    case 'l':
    case 'L':
        if(player.take_money(GLUE_COST))
        {
            towers.push_back(new Glue(deploay_position,this));
            return true;
        }
        break;
    default:
        add_error(new Error(Error::invalid_key));
        return false;
        break;
    }

    add_error(new Error(Error::money_error));
    return false;
}


Point World::align_point(Point source)
{
    auto aligned_point = (source - origin + Point(tile_size/2 , tile_size/2)) / tile_size;

    aligned_point *= tile_size;
    aligned_point += origin;   

    return aligned_point;
}

void World::do_areal_damage(Point center, int radius ,int damage)
{
    for(Enemy * enemy : enemies)
        if(enemy->position.distance(center) < radius*radius)
            enemy ->take_damage(damage);
}

void World::check_round(){

    if(player.is_lose())
    {
        window.show_text ("You Lose! afarin", Point(400,400), RGB(200,50,11), "Assets/OpenSans.ttf", 80);
        current_round = rounds.size() + 1;
    }

    if(current_round < rounds.size())
    if(!rounds[current_round].update() && !enemies.size())
    {
        current_round++;
        stringstream stream;
        stream << "Round " << current_round + 1;

        window.show_text (stream.str(), Point(500,400), RGB(200,50,11), "Assets/OpenSans.ttf", 80);
        window.update_screen();

        enemies.clear();
        objects.clear();
        delay(ROUND_DEALY);
    }
    if(current_round == rounds.size())
    {
        window.show_text ("You Win! afarin", Point(400,400), RGB(200,50,11), "Assets/OpenSans.ttf", 80);
    }
    window.update_screen();
}

bool World::handle_events()
{
    while (window.has_pending_event())
    {
        auto event = window.poll_for_event();
        switch (event.get_type())
        {
        case Event::EventType::QUIT :
            return true;     
            break; 
        case Event::EventType::LCLICK :
            if(last_click_pos == NULL)
                last_click_pos = new Point(event.get_mouse_position());
            else
                *last_click_pos = event.get_mouse_position();
            
            break;
        case Event::EventType::KEY_PRESS :
            handle_key_press(event.get_pressed_key());
            break;
        }
    }
    return false;
}

void  World::draw_all()
{

    window.clear();
    window.draw_img("Assets/background.png");

    draw_hud(last_click_pos);

    draw_towers();
    draw_enemies();
    draw_objects();
}

void World::do_areal_slow_down(Point center, int radius ,int percent ,int slow_down_time)
{
    for(Enemy * enemy : enemies)
            if(enemy->position.distance(center) < radius*radius)
                enemy ->slow_down(percent, slow_down_time);
}

Point World::point_to_location(Point point)
{
    auto diff = point - origin + Point(tile_size,tile_size) / 2;
    return diff / tile_size;
}

void World::add_error(Error* error)
{
    errors.push_back(error);
}

