#include "Runner.hpp"

Runner::Runner(Point position, Direction direction, World* world)
    : Enemy(RUNNER_HP, RUNNER_SPEED, RUNNER_DIE_REWARD, RUNNER_PUNISH, position, direction, world, "soldier_")
{
    enemy_type = ENEMY_TYPE::RUNNER;
    size = 85;
}