#include "../Source/Tower.hpp"

#define SLOWDOWN_DURATION  2500

class Glue : public Tower
{
private:
    int slow_down_duration;
    int slow_down_upgrade;
    void attack();
    void custom_level_up();

public:
    Glue(Point position,World* world);
    Window& operator>>(Window& window);
};


