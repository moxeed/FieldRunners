#include "Garphic.hpp"

void Graphic::draw_towers(VE)
{
    for (Tower* tower : world->towers)
        *tower >> window;
}

void Graphic::draw_enemies()
{
    for (auto enemy = enemies.rbegin(); enemy != enemies.rend() ; enemy++) 
        **enemy >> window;
}

void Graphic::update_objects()
{
    for(auto object = objects.cbegin(); object != objects.cend();)
    {
        if((*object)->is_delete_time())
        {  
            (*object)->update();
            delete *object;
            objects.erase(object++);
        }
        else
        {
            (*object)->update();
            object ++;
        }
    }
}
void Graphic::draw_objects()
{
    for(GameObject* object : objects)
        *object >> window;
}


void Graphic::draw_hud(Point* select_pos)
{
    if(select_pos != NULL)
    {
        auto mouse_pos = align_point(*select_pos);
        window.draw_rect(Rectangle( mouse_pos - Point(tile_size/2,tile_size/2) ,
                                    mouse_pos + Point(tile_size/2,tile_size/2)));
    }
    player >> window;
}