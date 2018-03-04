    #include "Txlib.h"

struct Player
    {
    private:

    double x_, y_, vx_, vy_;
    int moveR_, moveL_, moveU_, moveD_;


    public:

    Player (double xUser, double yUser, double vxUser, double vyUser, double moveRUser, double moveLUser, double moveUUser, double moveDUser, double scoreUser);

    void drawAsWasher ();
    void draw ();
    void physics (int dt);
    void control ();

    friend int Contact (Player AnyPlayer, Player *washer);

    int score;
    };

void GameOver ();
double sqr (double x);
void GameProcess ();

int main ()
    {
    txCreateWindow (1000, 600);

    GameProcess ();
    }

void GameProcess ()
    {
    Player washer   (500, 300, 50, 50, 0, 0, 0, 0, 0);
    Player player1  (50, 300, 0, 15, 'D', 'A', 'W', 'S', 0);
    Player player2  (950, 300, 0, 15, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 0);
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

        washer.physics (dt);
        player1.physics (dt);
        player2.physics (dt);

        player1.control ();
        player2.control ();

        player1.score += Contact (player1, &washer);
        player2.score += Contact (player2, &washer);

        txSetFillColor (TX_BLACK);
        txSetColor (TX_LIGHTCYAN);
        txRectangle (600, 0, 1000, 200);

        itoa (player1.score, scoreOut1, 10);
        itoa (player2.score, scoreOut2, 10);

        txTextOut (730, 20, "Player1 = "); txTextOut (830, 20, scoreOut1);
        txTextOut (730, 60, "Player2 = "); txTextOut (830, 60, scoreOut2);

        washer.drawAsWasher ();

        player1.draw ();

        player2.draw ();

        txSleep (150);
        }
    }

Player:: Player (double xUser,     double yUser,     double vxUser,    double vyUser,
                 double moveRUser, double moveLUser, double moveUUser, double moveDUser, double scoreUser) :
    x_ (xUser),
    y_ (yUser),
    vx_ (vxUser),
    vy_ (vyUser),
    moveR_ (moveRUser),
    moveL_ (moveLUser),
    moveU_ (moveUUser),
    moveD_ (moveDUser)

    {

    }

void Player:: physics (int dt)
    {
    double Friction = 0.9999;

    x_ = x_ + vx_ * dt;
    y_ = y_ + vy_ * dt;

    vx_ = vx_ * Friction;
    vy_ = vy_ * Friction;


    if (x_ > 1000)
        {
        x_ = 1000;
        vx_ = - vx_;
        }

    if (x_ < 0)
        {
        x_ = 0;
        vx_ = - vx_;
        }

    if (y_ > 600)
        {
        y_ = 600;
        vy_ = - vy_;
        }

    if (y_ < 0)
        {
        x_ = 0;
        vy_ = - vy_;
        }
    }

void Player:: control ()
    {
    if ( GetAsyncKeyState (moveR_))
        {
        vx_ = 5;
        }

    if ( GetAsyncKeyState (moveL_))
        {
        vx_ = -5;
        }

    if ( GetAsyncKeyState (moveU_))
        {
        vy_ = -5;
        }

    if ( GetAsyncKeyState (moveD_))
        {
        vy_ = 5;
        }
    }

int Contact (Player AnyPlayer, Player *washer)
    {
    if (sqrt(sqr(AnyPlayer.x_ - washer->x_) + sqr(AnyPlayer.y_ - washer->y_)) < 30 + 40)
        {
        washer->vx_ = AnyPlayer.vx_;
        washer->vy_ = AnyPlayer.vy_;

        washer->x_ = washer->x_ + washer->vx_;
        washer->y_ = washer->y_+ washer->vy_;
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

void Player:: drawAsWasher ()
    {
    txSetFillColor (TX_RED);
    txSetColor (TX_WHITE);
    txCircle (x_, y_, 30);
    }

void Player:: draw ()
    {
    char scoreOut [4] = "";
    itoa (score, scoreOut, 10);

    txSetFillColor (TX_BLUE);
    txSetColor (TX_WHITE);
    txCircle (x_, y_, 40);

    txSetTextAlign (TA_CENTER);
    txTextOut (x_, y_ - 7, scoreOut);
    }
