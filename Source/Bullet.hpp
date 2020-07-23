#include "GameObject.hpp"
#include "../Animation/Animation.hpp"

#ifndef BULLET_HEADER
#define BULLET_HEADER

class Enemy;
class Animation;

class Bullet : public GameObject 
{
private :
    int size = 30;
    int speed = 100;

    Animation animation;

    bool is_reached();

protected:
    int damage = 100;

    Enemy* target;

public :
    Bullet (int _speed, Point position, World* world ,std::string animation_name);
    
    bool is_delete_time();
    void update();
    virtual void do_damage() = 0;

    Window& operator >> (Window& window);
};

#endif