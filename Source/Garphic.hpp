#include "../RSDL/rsdl.hpp"

class World;

class Garphic
{
private:

    static constexpr int screen_width = 1365;
    static constexpr int screen_heght = 1024;
    const int tile_size = 60;
    const int object_size = 80;

    World* world;
    Window* window;

    void draw_enemies();
    void draw_towers();
    void draw_objects(); 
    void draw_hud(Point* select_pos);

public:
    Garphic(World* World);
    void draw_all();
};