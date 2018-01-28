    #include "Txlib.h"

struct Player
    {
    double x, y, vx, vy;
    };

void GameProcess ();
void Physics (double* x, double* y, double* vx, double* vy, int dt,int isPlayer);
void Control (double* vxPlayer1, double* vyPlayer1, double* vxPlayer2, double* vyPlayer2);
void GameOver ();
void Contact (double xAnyPlayer, double yAnyPlayer, double vxAnyPlayer, double vyAnyPlayer, double* xWasher, double* yWasher, double* vxWasher, double* vyWasher);
double sqr (double x);

int main ()
    {
    txCreateWindow (1000, 600);

    GameProcess ();
    }

void GameProcess ()
    {
    Player washer  = {500, 300, 50, 50};
    Player Player1 = {50, 300, 0, 15};
    Player Player2 = {950, 300, 0, 15};
    int dt = 1;

    while ( ! GetAsyncKeyState (VK_RETURN))
        {
        txSetColor (TX_BLUE, 8);
        txLine (4, 280, 4, 320);

        txSetColor (TX_BLUE, 8);
        txLine (996, 280, 996, 320);

        txSetFillColor (TX_YELLOW);
        txClear ();

        txSetFillColor (TX_RED);
        txSetColor (TX_WHITE);
        txCircle (washer.x, washer.y, 30);

        txSetFillColor (TX_BLUE);
        txSetColor (TX_WHITE);
        txCircle (Player1.x, Player1.y, 40);
        txSelectFont ("Arial", 30);
        txDrawText (Player1.x - 15, Player1.y - 15, Player1.x + 15, Player1.y + 15, "1");


        txSetFillColor (TX_BLUE);
        txSetColor (TX_WHITE);
        txCircle (Player2.x, Player2.y, 40);
        txDrawText (Player2.x - 15, Player2.y - 15, Player2.x + 15, Player2.y + 15, "2");


        Physics (&washer.x,  &washer.y,  &washer.vx,  &washer.vy,  dt, false);
        Physics (&Player1.x, &Player1.y, &Player1.vx, &Player1.vy, dt, true);
        Physics (&Player2.x, &Player2.y, &Player2.vx, &Player2.vy, dt, true);

        Control (&Player1.vx, &Player1.vy, &Player2.vx, &Player2.vy);

        Contact (Player1.x, Player1.y, Player1.vx, Player1.vy, &washer.x, &washer.y, &washer.vx, &washer.vy);
        Contact (Player2.x, Player2.y, Player2.vx, Player2.vy, &washer.x, &washer.y, &washer.vx, &washer.vy);

        txSleep (100);
        }
    }

void Physics (double* x, double* y, double* vx, double* vy, int dt, int isPlayer)
    {
    double Friction = 0.9999;

    *x = *x + *vx*dt;
    *y = *y + *vy*dt;

    *vx = *vx * Friction;
    *vy = *vy * Friction;


    if (*x > 1000)
        {
        *x = 1000;
        *vx = -*vx;
        }

    if (*x < 0)
        {
        *x = 0;
        *vx = -*vx;
        }

    if (*y > 600)
        {
        *y = 600;
        *vy = -*vy;
        }

    if (*y < 0)
        {
        *x = 0;
        *vy = -*vy;
        }
    }

void Control (double* vxPlayer1, double* vyPlayer1, double* vxPlayer2, double* vyPlayer2)
    {
    if ( GetAsyncKeyState (VK_RIGHT))
        {
        *vxPlayer1 = 5;
        }

    if ( GetAsyncKeyState (VK_LEFT))
        {
        *vxPlayer1 = -5;
        }

    if ( GetAsyncKeyState (VK_UP))
        {
        *vyPlayer1 = -5;
        }

    if ( GetAsyncKeyState (VK_DOWN))
        {
        *vyPlayer1 = 5;
        }

    if ( GetAsyncKeyState ('D'))
        {
        *vxPlayer2 = 5;
        }

    if ( GetAsyncKeyState ('A'))
        {
        *vxPlayer2 = -5;
        }

    if ( GetAsyncKeyState ('W'))
        {
        *vyPlayer2 = -5;
        }

    if ( GetAsyncKeyState ('S'))
        {
        *vyPlayer2 = 5;
        }
    }

void Contact (double xAnyPlayer, double yAnyPlayer, double vxAnyPlayer, double vyAnyPlayer, double* xWasher, double* yWasher, double* vxWasher, double* vyWasher)
    {
    if (sqrt(sqr(xAnyPlayer - *xWasher) + sqr(yAnyPlayer - *yWasher)) < 30 + 40)
        {
        *vxWasher = vxAnyPlayer;
        *vyWasher = vyAnyPlayer;

        *xWasher = *xWasher + *vxWasher;
        *yWasher = *yWasher + *vyWasher;
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
