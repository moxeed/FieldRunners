#include "../RSDL/rsdl.hpp"

#ifndef GAMEOBJECT_HEADER
#define GAMEOBJECT_HEADER

#define ERROR 9

class Assets;
class World;

class GameObject
{
protected:
    World * world;

public:    
    Point position;

    virtual Window& operator >> (Window& window) = 0;
    virtual void update() = 0;
    virtual bool is_delete_time() { return false; }

    GameObject(Point pos,World* _world);
};

#endif
