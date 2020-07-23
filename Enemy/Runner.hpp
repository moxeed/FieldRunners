#include "../Source/Enemy.hpp"

class Runner : public Enemy
{
public:
    Runner(Point position, Direction direction, World* world);
};
