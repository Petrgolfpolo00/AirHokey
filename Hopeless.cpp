    #include "Txlib.h"

struct Charecter
    {
    private:

    int x0_, y0_, vx_, vy_;
    int x1_, y1_;
    int x2_, y2_;

    public:

    Charecter (int xUser, int yUser, int vxUser, int vyUser);

    void charecterDraw ();
    void physics (int dt);
    void control ();
    };

void MainCycle ();

int main ()
    {
    txCreateWindow (500, 250);

    MainCycle ();
    }

void MainCycle ()
    {
    Charecter snake (250, 125, 0, 0);
    int dt = 1;

    while ( ! GetAsyncKeyState (VK_RETURN))
        {
        txSetFillColor (TX_WHITE);
        txClear ();

        snake.control ();
        snake.physics (dt);
        snake.charecterDraw ();

        txSleep (100);
        }
    }

Charecter:: Charecter (int xUser, int yUser, int vxUser, int vyUser) :

    x0_ (xUser),
    y0_ (yUser),

    x1_ (xUser),
    y1_ (yUser),

    x2_ (xUser),
    y2_ (yUser),

    vx_ (vxUser),
    vy_ (vyUser)


    {
    }

void Charecter:: physics (int dt)
    {
    x2_ = x1_;
    y2_ = y1_;

    x1_ = x0_;
    y1_ = y0_;

    x0_ = x0_ + vx_ * dt;
    y0_ = y0_ + vy_ * dt;

    if (x0_ > 530)
        {
        x0_ = -30;
        }

    if (x0_ < -30)
        {
        x0_ = 530;
        }

    if (y0_ > 280)
        {
        y0_ = -30;
        }

    if (y0_ < -30)
        {
        y0_ = 280;
        }
    }

void Charecter:: control ()
    {
    if (GetAsyncKeyState (VK_RIGHT))
        {
        vx_ = 7;
        vy_ = 0;
        }

    if (GetAsyncKeyState (VK_LEFT))
        {
        vx_ = -7;
        vy_ = 0;
        }

    if (GetAsyncKeyState (VK_UP))
        {
        vy_ = -7;
        vx_ = 0;
        }

    if (GetAsyncKeyState (VK_DOWN))
        {
        vy_ = 7;
        vx_ = 0;
        }
    }

void Charecter:: charecterDraw ()
    {
    txSetFillColor (TX_BLUE);
    txRectangle (x0_ - 5, y0_ - 5, x0_ + 5, y0_ + 5);

    txSetFillColor (TX_RED);
    txRectangle (x1_ - 5, y1_ - 5, x1_ + 5, y1_ + 5);

    txSetFillColor (TX_GREEN);
    txRectangle (x2_ - 5, y2_ - 5, x2_ + 5, y2_ + 5);
    }
