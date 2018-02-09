    #include "Txlib.h"

struct Player
    {
    double x, y, vx, vy;
    char* text;
    };

void GameProcess ();
void Physics (Player* player, int dt, int isPlayer);
void Control (Player* player);
void GameOver ();
void Contact (Player* player, Player* washer);
double sqr (double x);
void DrowWasher (Player washer);
void DrowPlayer (Player player);

int main ()
    {
    txCreateWindow (1000, 600);

    GameProcess ();
    }

void GameProcess ()
    {
    Player washer  = {500, 300, 50, 50};
    Player player1 = { 50, 300,  0, 15, "1"};
    Player player2 = {950, 300,  0, 15, "2"};
    int dt = 1;

    while ( ! GetAsyncKeyState (VK_RETURN))
        {
        txSetColor (TX_BLUE, 8);
        txLine (4, 280, 4, 320);

        txSetColor (TX_BLUE, 8);
        txLine (996, 280, 996, 320);

        txSetFillColor (TX_YELLOW);
        txClear ();

        DrowWasher (washer);
        DrowPlayer (player1);
        DrowPlayer (player2);


        Physics (&washer,  dt, false);
        Physics (&player1, dt, true);
        Physics (&player2, dt, true);

        Control (&player1);
        Control (&player2);

        Contact (&player1, &washer);
        Contact (&player2, &washer);

        txSleep (100);
        }
    }

void Physics (Player* player, int dt, int isPlayer)
    {
    double Friction = 0.9999;

    (*player).x = (*player).x + (*player).vx*dt;
    player->y = player->y + player->vy*dt;

    player->vx = player->vx * Friction;
    player->vy = player->vy * Friction;


    if (player->x > 1000)
        {
        player->x = 1000;
        player->vx = - player->vx;
        }

    if (player->x < 0)
        {
        player->x = 0;
        player->vx = - player->vx;
        }

    if (player->y > 600)
        {
        player->y = 600;
        player->vy = - player->vy;
        }

    if (player->y < 0)
        {
        player->x = 0;
        player->vy = - player->vy;
        }
    }

void Control (Player* player)
    {
    if ( GetAsyncKeyState (VK_RIGHT))
        {
        player->vx = 5;
        }

    if ( GetAsyncKeyState (VK_LEFT))
        {
        player->vx = -5;
        }

    if ( GetAsyncKeyState (VK_UP))
        {
        player->vy = -5;
        }

    if ( GetAsyncKeyState (VK_DOWN))
        {
        player->vy = 5;
        }
    }

void Contact (Player* player, Player* washer)
    {
    if (sqrt(sqr(player->x - washer->x) + sqr(player->y - washer->y)) < 30 + 40)
        {
        washer->vx = player->vx;
        washer->vy = player->vy;

        washer->x = washer->x + washer->vx;
        washer->y = washer->y + washer->vy;
        }
    }

void GameOver ()
    {
    txSetColor (TX_PINK, 10);
    txSelectFont ("Arial", 30);
    txDrawText (50, 50, 150, 70, "GAME OVER");
    }

double sqr (double x)
    {
    return x*x;
    }

void DrowWasher (Player washer)
    {
    txSetFillColor (TX_RED);
    txSetColor (TX_WHITE);
    txCircle (washer.x, washer.y, 30);
    }

void DrowPlayer (Player player)
    {
    txSetFillColor (TX_BLUE);
    txSetColor (TX_WHITE);
    txCircle (player.x, player.y, 40);
    txDrawText (player.x - 15, player.y - 15, player.x + 15, player.y + 15, player.text);
    }
