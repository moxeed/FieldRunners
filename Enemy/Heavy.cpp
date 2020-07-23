#include "Heavy.hpp"
#include "../Source/Enemy.hpp"

Heavy::Heavy(Point position, Direction direction, World* world)
    : Enemy(HEAVY_HP, HEAVY_SPEED, HEAVY_DIE_REWARD, HEAVY_PUNISH, position, direction, world, "heavy_")
{
    enemy_type = ENEMY_TYPE::HEAVY;
    size = 65;
}