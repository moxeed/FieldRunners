#include "Assets.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

#ifndef ASSETS_BODY
#define ASSETS_BODY

using namespace std;

Assets::Assets()
{   
    enemy_route = new LinkedList<Point>(Point(0,0));
    
    read_route_data();
    generate_animations();
}

void Assets::generate_animations()
{
    string animation_name,file_address;
    int start_frame,end_frame;
    ifstream animation_map("Assets/AnimationMap.txt");

    while (animation_map >> animation_name >> file_address >> start_frame >> end_frame)
    {
        animations[animation_name] = 
        Animation(generate_animation_images(file_address,start_frame,end_frame),20);

    }
}

vector<string> Assets::generate_animation_images(string name,int start,int end)
{
    vector<string> names;
    for(int i=start; i <= end; i++)
    {
        stringstream stream;

        stream << name;
        stream << i;
        stream << ".png";

        names.push_back(stream.str());
    }

    return names;
}

Animation Assets::get_anmation(std::string animation_name)
{
    return animations[animation_name];
}

void Assets::read_route_data()
{
    string route_data;
    getline(cin,route_data);
    stringstream stream(route_data);
    LinkedList<Point> * prev = enemy_route;

    int x,y;
    while (stream >> x >> y)
    {
        LinkedList<Point> * route_part = new LinkedList<Point>(Point(x,y));
        prev->next = route_part;
        prev = route_part;
    }

    set_route_tile_state();
}

void Assets::set_route_tile_state()
{
    auto current_node = enemy_route->next;
    
    while(current_node->next != NULL)
    {
        auto destination = current_node->next;

        if(destination->value.x == current_node->value.x)
        {
            int min = destination->value.y < current_node->value.y ? destination->value.y : current_node->value.y;
            int max = destination->value.y > current_node->value.y ? destination->value.y : current_node->value.y;  

            for (int i = min; i <= max ;i++)
            {
                tile_states[i][destination->value.x] = TILE_STATE::FULL;
            }
        }

        if(destination->value.y == current_node->value.y)
        {
            int min = destination->value.x < current_node->value.x ? destination->value.x : current_node->value.x;
            int max = destination->value.x > current_node->value.x ? destination->value.x : current_node->value.x;  

            for (int i = min; i <= max ;i++)
            {
                tile_states[destination->value.y][i] = TILE_STATE::FULL;
            }
        }

        current_node = destination;
    }
}

TILE_STATE Assets::get_tile_state(Point pos)
{
    return tile_states[pos.y][pos.x];
}
void Assets::set_tile_state(Point pos,TILE_STATE state)
{
    tile_states[pos.y][pos.x] = state;
}

Error::Error(std::string msg , int time)
{
    message = msg;
    remain_time = time;
}
Window& Error::operator>> (Window& window)
{
    remain_time --;
    window.show_text(message, Point(685 - 12 * message.size() ,50), 
        WHITE, "Assets/OpenSans.ttf", 45);
    return window;
}

bool Error::is_delete_time()
{
    return remain_time <= 0;
}

Error Error::money_error = Error("Not Enough Money! Kill More", 15);
Error Error::max_level = Error("Max Level! What Do U Expect?", 15);
Error Error::no_choose = Error("First Select A Pos", 15);
Error Error::full_house = Error("Already Taken!", 15);
Error Error::invalid_key = Error("Invalid Key", 15);

#endif


