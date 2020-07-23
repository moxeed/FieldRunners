#include "GameObject.hpp"
#include "../Animation/Animation.hpp"
#include "LinkedList.hpp"

#include <string>

#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#define RUNNER_HP 250
#define ICERUNNER_HP 400
#define HEAVY_HP 500
#define BIKE_HP 100

#define RUNNER_SPEED 50
#define ICERUNNER_SPEED 32
#define HEAVY_SPEED 25
#define BIKE_SPEED 90

#define RUNNER_DIE_REWARD 6
#define ICERUNNER_DIE_REWARD 10
#define HEAVY_DIE_REWARD 8
#define BIKE_DIE_REWARD 4

#define RUNNER_PUNISH 1
#define ICERUNNER_PUNISH 4
#define HEAVY_PUNISH 4
#define BIKE_PUNISH  2


enum ENEMY_TYPE 
{
    BIKE     ,
    HEAVY    ,
    RUNNER   ,
    ICERUNNER
};


class Direction
{
    int x_scale;
    int y_scale;

public :
    std::string identifier;

    Direction(int _x_scale,int _y_scale,std::string _identifier);
    Direction(Point point);

    Direction operator * (int speed);
    Point operator + (Point pos);
    bool operator == (Direction direction);
};

class Directions
{
public :
    static Direction up;
    static Direction down;
    static Direction left;
    static Direction right;
};

class Enemy : public GameObject
{
private:
    int hit_point;
    float speed;
    int defalut_speed;
    int die_reward;
    int reach_punish;
    int x_displace = 5;
    int y_displace = -15;
    int slow_down_time;


    LinkedList<Point>* destination;
    Direction direction;
    
    Animation current_animation;

    Point find_next_destination();
    bool is_reached();
    void die();
    void set_animation(); 
    void success();

protected :
    int size;
    std::string animation_prefix;

public:
    ENEMY_TYPE enemy_type;

    Window& operator>> (Window& window);
    Enemy(int _hit_point, int _speed, int _die_reward, int _reach_punish,
        Point pos, Direction dirction, World* world,std::string prefix);

    bool is_died();
    void update();
    void take_damage(int value);
    void slow_down(int percent,int time);
    Point get_position();
};

#endif