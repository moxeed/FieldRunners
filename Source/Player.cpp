#include "Player.hpp"
#include "../RSDL/rsdl.hpp"

#include<sstream>

using namespace std;

Player::Player()
{
    health = PLAYER_INIT_HP;
    currency = PLAYER_INIT_CURRENCY; 
}

Player::Player(int init_health,int init_currency)
{
    health = init_health;
    currency = init_currency; 
}

void Player::loss_health(int loss)
{
    health -= loss;
}

void Player::take_reward(int reward)
{
    currency += reward;
}

Window& Player::operator >> (Window& window)
{
    stringstream stream;
    stream << health;
    window.show_text(stream.str(),Point(100,30));

    stream.str("");
    stream << currency;
    window.show_text(stream.str(),Point(1200,30));

    return window;
}

bool Player::take_money(int value)
{
    if(value > currency)
        return false;

    currency -= value;
    return true;
}

bool Player::is_lose()
{
    return health <= 0;
}


