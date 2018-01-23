    #include "Txlib.h"

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
    double xWasher = 500, yWasher = 300, vxWasher = 50, vyWasher = 50;
    double xPlayer1 = 50, yPlayer1 = 300, vxPlayer1 = 0, vyPlayer1 = 15;
    double xPlayer2 = 950, yPlayer2 = 300, vxPlayer2 = 0, vyPlayer2 = 15;
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
        txCircle (xWasher, yWasher, 30);

        txSetFillColor (TX_BLUE);
        txSetColor (TX_WHITE);
        txCircle (xPlayer1, yPlayer1, 40);
        txSelectFont ("Arial", 30);
        txDrawText (xPlayer1 - 15, yPlayer1 - 15, xPlayer1 + 15, yPlayer1 + 15, "1");


        txSetFillColor (TX_BLUE);
        txSetColor (TX_WHITE);
        txCircle (xPlayer2, yPlayer2, 40);
        txDrawText (xPlayer2 - 15, yPlayer2 - 15, xPlayer2 + 15, yPlayer2 + 15, "2");


        Physics (&xWasher,  &yWasher,  &vxWasher,  &vyWasher,  dt, false);
        Physics (&xPlayer1, &yPlayer1, &vxPlayer1, &vyPlayer1, dt, true);
        Physics (&xPlayer2, &yPlayer2, &vxPlayer2, &vyPlayer2, dt, true);

        Control (&vxPlayer1, &vyPlayer1, &vxPlayer2, &vyPlayer2);

        Contact (xPlayer1, yPlayer1, vxPlayer1, vyPlayer1, &xWasher, &yWasher, &vxWasher, &vyWasher);
        Contact (xPlayer2, yPlayer2, vxPlayer2, vyPlayer2, &xWasher, &yWasher, &vxWasher, &vyWasher);

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
