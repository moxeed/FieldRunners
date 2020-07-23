#include "../Source/Enemy.hpp"

class Heavy : public Enemy
{
public:
    Heavy(Point position, Direction direction, World* world);
};
