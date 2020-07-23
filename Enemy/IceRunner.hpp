#include "../Source/Enemy.hpp"

class IceRunner : public Enemy
{
public:
    IceRunner(Point position, Direction direction, World* world);
};
