#include "../Source/Tower.hpp"

class Missle : public Tower
{
private:
    void attack();
public:
    Missle(Point position,World* world);
    Window& operator>>(Window& window);
};


