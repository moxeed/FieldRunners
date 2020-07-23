#include "../Source/Tower.hpp"

class Gattling : public Tower
{
private:
    void attack();
public:
    Gattling(Point position,World* world);
    Window& operator>>(Window& window);
};


