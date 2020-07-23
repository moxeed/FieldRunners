
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#define PLAYER_INIT_HP 20
#define PLAYER_INIT_CURRENCY 200

class Window;

class Player
{
private:
    int currency;
    int health;
public:
    Player();
    Player(int init_health,int init_currency);
    void take_reward(int reward);
    void loss_health(int loss);
    bool is_lose();
    bool take_money(int value);

    Window& operator >> (Window& window);
};

#endif