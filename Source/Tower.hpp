#include "GameObject.hpp"
#include <chrono>

#ifndef TOWER_HEADER
#define TOWER_HEADER

class Enemy;
class Bullet;

#define MAX_TOWER_LEVEL 3
#define ATTACK_MODE_DURATION 3

#define GATTLING_COOLDOWN                 1
#define GATTLING_COST                     55
#define GATTLING_UPGRADECOST              40
#define GATTLING_DAMAGE                   35
#define GATTLING_UPGRADE_DAMAGE_INCREASE  35

#define MISSLE_COOLDOWN                   3
#define MISSLE_COST                       70
#define MISSLE_UPGRADECOST                60
#define MISSLE_DAMAGE                     75
#define MISSLE_UPGRADE_DAMAGE_INCREASE    75

#define TESLA_COOLDOWN                     1.5
#define TESLA_COST                         120
#define TESLA_UPGRADECOST                  100
#define TESLA_DAMAGE                       700
#define TESLA_UPGRADE_DAMAGE_INCREASE      1000

#define GLUE_COOLDOWN                    2
#define GLUE_COST                        60
#define GLUE_UPGRADECOST                 45
#define GLUE_DAMAGE                      40
#define GLUE_UPGRADE_DAMAGE_INCREASE     10

enum TowerDirection
{
    DEG0   = 1,
    DEG10  = 2,
    DEG20  = 3,
    DEG30  = 4,
    DEG40  = 5,
    DEG50  = 6,
    DEG60  = 7,
    DEG70  = 8,
    DEG80  = 9,
    DEG90  = 10,
    DEG100 = 11,
    DEG110 = 12,
    DEG130 = 13,
    DEG140 = 14,
    DEG150 = 15,
    DEG160 = 16,
    DEG170 = 17,
    DEG180 = 18,
};

class Tower : public GameObject
{
private:

    typedef std::chrono::steady_clock clock;
    typedef std::chrono::duration<float> time_span;


    std::chrono::steady_clock::time_point last_attack;

protected:
    Enemy* target;
    Bullet* bullet;
    
    float cool_down;
    int cost;
    int damage;
    int attack_mode;
    int upgrade_cost;
    int upgrade_damage_increase;
    int level = 1;
    int range = 200;

    int direction;
    void set_direction();
    bool is_attack_time();
    bool is_enemy_in_range();

    virtual void attack() = 0;
    virtual void custom_level_up(){};
protected:
    void set_tagret();
public:
    Tower(Point pos,World* world);
    void level_up();
    void update();
};

#endif