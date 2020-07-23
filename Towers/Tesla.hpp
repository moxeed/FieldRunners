#include "../Source/Tower.hpp"

class Tesla : public Tower
{
private:
    void attack();
public:
    Tesla(Point position,World* world);
    Window& operator>>(Window& window);
};


