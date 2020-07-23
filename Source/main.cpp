#include "../Animation/Animation.hpp"
#include "../RSDL/rsdl.hpp"
#include "Enemy.hpp"
#include "World.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    bool quit = false;
    World world;
    /*Window window(1024,1024,"Filed Runners");

    vector<string> names;
    for(int i=0; i<12; i++)
    {
        stringstream stream;
        stream << "Assets/Runner/solider_run_up_";
        stream << i;
        stream << ".png";

        names.push_back(stream.str());
    }

    Animation anim(names,20);
    Enemy enemy (20,10,5,Point(10,10),Directions::right,anim);
    */
    while(!quit)
    {
        quit = world.update();
        /*window.clear();

        while (window.has_pending_event())
        {
            auto event = window.poll_for_event();

            switch (event.get_type())
            {
                case Event::EventType::QUIT :
                    quit = true;     
                    break;

            }
            
        }
        enemy.update();
        enemy >> window;

        window.draw_img(anim.get_current_frame_name(),Rectangle(100,100,40,50));

        window.update_screen();

        delay(50);*/
    }

    return 0;
}