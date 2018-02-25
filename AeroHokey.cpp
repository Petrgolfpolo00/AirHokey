    #include "Txlib.h"

struct Player
    {
    double x, y, vx, vy;
    int moveR, moveL, moveU, moveD;
    int score;
    };

void GameProcess ();
void Physics (Player* player, int dt, int isPlayer);
void Control (Player* player);
void GameOver ();
int Contact (double xAnyPlayer, double yAnyPlayer, double vxAnyPlayer, double vyAnyPlayer, double* xWasher, double* yWasher, double* vxWasher, double* vyWasher);
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
    Player player1 = {50, 300, 0, 15, 'D', 'A', 'W', 'S', 0};
    Player player2 = {950, 300, 0, 15, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 0};
    int dt = 1;
    char scoreOut1 [4] = "";
    char scoreOut2 [4] = "";

    while ( ! GetAsyncKeyState (VK_RETURN))
        {
        txSetFillColor (TX_YELLOW);

        txClear ();

        txSetColor (TX_BLUE, 8);
        txLine (4, 280, 4, 320);

        txSetColor (TX_BLUE, 8);
        txLine (996, 280, 996, 320);

        Physics (&washer,  dt, false);
        Physics (&player1, dt, true);
        Physics (&player2, dt, true);

        Control (&player1);
        Control (&player2);

        player1.score += Contact (player1.x, player1.y, player1.vx, player1.vy, &washer.x, &washer.y, &washer.vx, &washer.vy);
        player2.score += Contact (player2.x, player2.y, player2.vx, player2.vy, &washer.x, &washer.y, &washer.vx, &washer.vy);

        txSetFillColor (TX_BLACK);
        txSetColor (TX_LIGHTCYAN);
        txRectangle (600, 0, 1000, 200);

        itoa (player1.score, scoreOut1, 10);
        itoa (player2.score, scoreOut2, 10);

        txTextOut (730, 20, "Player1 = "); txTextOut (830, 20, scoreOut1);
        txTextOut (730, 60, "Player2 = "); txTextOut (830, 60, scoreOut2);

        DrowWasher (washer);

        DrowPlayer (player1);

        DrowPlayer (player2);

        txSleep (150);
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
    if ( GetAsyncKeyState (player->moveR))
        {
        player->vx = 5;
        }

    if ( GetAsyncKeyState (player->moveL))
        {
        player->vx = -5;
        }

    if ( GetAsyncKeyState (player->moveU))
        {
        player->vy = -5;
        }

    if ( GetAsyncKeyState (player->moveD))
        {
        player->vy = 5;
        }
    }

int Contact (double xAnyPlayer, double yAnyPlayer, double vxAnyPlayer, double vyAnyPlayer, double* xWasher, double* yWasher, double* vxWasher, double* vyWasher)
    {
    if (sqrt(sqr(xAnyPlayer - *xWasher) + sqr(yAnyPlayer - *yWasher)) < 30 + 40)
        {
        *vxWasher = vxAnyPlayer;
        *vyWasher = vyAnyPlayer;

        *xWasher = *xWasher + *vxWasher;
        *yWasher = *yWasher + *vyWasher;
        return 1;
        }
    return 0;
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
    char scoreOut [4] = "";
    itoa (player.score, scoreOut, 10);

    txSetFillColor (TX_BLUE);
    txSetColor (TX_WHITE);
    txCircle (player.x, player.y, 40);

    txSetTextAlign (TA_CENTER);
    txTextOut (player.x, player.y - 7, scoreOut);
    }
