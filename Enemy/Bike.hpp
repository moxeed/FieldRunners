#include "../Source/Enemy.hpp"

class Bike : public Enemy
{
public:
    Bike(Point position, Direction direction, World* world);
};
