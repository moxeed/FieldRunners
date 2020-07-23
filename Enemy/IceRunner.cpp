#include "IceRunner.hpp"
#include "../Source/Enemy.hpp"

IceRunner::IceRunner(Point position, Direction direction, World* world)
    : Enemy(ICERUNNER_HP, ICERUNNER_SPEED, ICERUNNER_DIE_REWARD, ICERUNNER_PUNISH, position, direction, world, "ice_runner_")
{
    enemy_type = ENEMY_TYPE::ICERUNNER;
    size = 45;
}