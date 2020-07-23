#include "GameObject.hpp"


GameObject::GameObject(Point pos,World* _world) : position(pos)
{
    world = _world;
}