#include "../RSDL/rsdl.hpp"
#include "LinkedList.hpp"
#include <map>
#include <vector>
#include <string>
#include "../Animation/Animation.hpp"

#ifndef ASSETS_HEADER
#define ASSETS_HEADER

enum TILE_STATE
{
    EMPTY,
    FULL 
};

class Assets
{
private:
    std::map<std::string,Animation> animations;
    TILE_STATE tile_states[11][19]={0};

    void generate_animations();
    void read_route_data();
    void set_route_tile_state();
    std::vector<std::string> generate_animation_images(std::string name,int start,int end);
public:

    LinkedList<Point>* enemy_route;
    Assets();

    void set_tile_state(Point pos,TILE_STATE state);
    
    TILE_STATE get_tile_state(Point pos);
    Animation get_anmation(std::string animation_name);
};

class Error
{
private :

    std::string message;
    int remain_time;
public :

    static Error money_error;
    static Error max_level;
    static Error no_choose;
    static Error full_house;
    static Error invalid_key;

    Error(std::string msg , int time);

    bool is_delete_time();
    Window& operator>> (Window& window);
};

#endif