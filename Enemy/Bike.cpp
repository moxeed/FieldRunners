#include "Bike.hpp"
#include "../Source/Enemy.hpp"

Bike::Bike(Point position, Direction direction, World* world)
    : Enemy(BIKE_HP, BIKE_SPEED, BIKE_DIE_REWARD, BIKE_PUNISH, position, direction, world, "bike_")
{
    enemy_type = ENEMY_TYPE::BIKE;
    size = 90;
}
