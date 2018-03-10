    #include "Txlib.h"

const int SnakeSz = 100;
const int Zoom = 5;

struct Charecter
    {
    private:

    int length_;

    int x_[SnakeSz], y_[SnakeSz], vx_, vy_;

    public:

    Charecter (int xUser, int yUser, int vxUser, int vyUser);

    void charecterDraw ();
    void physics (int dt);
    void control ();
    void maybeEatFruite (int xFr, int yFr);
    };

void MainCycle ();
void DrawFruite (int x, int y);
void numberXchange (int x, int y);

int main ()
    {
    txCreateWindow (200 * Zoom, 100 * Zoom);

    MainCycle ();
    }

void MainCycle ()
    {
    Charecter snake (100 * Zoom, 50 * Zoom, 0 * Zoom, 0 * Zoom);
    int dt = 1;
    int xFr = 0;
    int yFr = 0;

    numberXchange (&xFr, &yFr);

    while ( ! GetAsyncKeyState (VK_RETURN))
        {
        txSetFillColor (TX_WHITE);
        txClear ();

        DrawFruite (xFr, yFr);

        snake.control ();
        snake.physics (dt);
        snake.charecterDraw ();
        snake.maybeEatFruite (xFr, yFr);

        txSleep (100);
        }
    }

Charecter:: Charecter (int xUser, int yUser, int vxUser, int vyUser) :

    x_ ({xUser}),
    y_ ({yUser}),

    vx_ (vxUser),
    vy_ (vyUser),

    length_ (1)

    {
    }

void Charecter:: physics (int dt)
    {

    for (int i = length_ - 1; i >= 1; i--)
        {
        x_[i] = x_[i-1];
        y_[i] = y_[i-1];
        }

    x_[0] = x_[0] + vx_ * dt;
    y_[0] = y_[0] + vy_ * dt;

    if (x_[0] > 200 * Zoom)
        {
        x_[0] = 0;
        }

    if (x_[0] < 0)
        {
        x_[0] = 200 * Zoom;
        }

    if (y_[0] > 100 * Zoom)
        {
        y_[0] = 0;
        }

    if (y_[0] < 0)
        {
        y_[0] = 100 * Zoom;
        }
    }

void Charecter:: control ()
    {
    if (GetAsyncKeyState (VK_RIGHT))
        {
        vx_ = 5 * Zoom;
        vy_ = 0;
        }

    if (GetAsyncKeyState (VK_LEFT))
        {
        vx_ = -5 * Zoom;
        vy_ = 0;
        }

    if (GetAsyncKeyState (VK_UP))
        {
        vy_ = -5 * Zoom;
        vx_ = 0;
        }

    if (GetAsyncKeyState (VK_DOWN))
        {
        vy_ = 5 * Zoom;
        vx_ = 0;
        }
    }

void Charecter:: charecterDraw ()
    {
    txSetFillColor (TX_BLUE);
    for (int i = 0; i < length_; i++) txRectangle (x_[i] - 5 * 0.5 * Zoom, y_[i] - 5 * 0.5 * Zoom, x_[i] + 5 * 0.5 * Zoom, y_[i] + 5 * 0.5 * Zoom);
    }

void DrawFruite (int x, int y)
    {
    txSetFillColor (TX_RED);
    txCircle (x, y, 6 * 0.5 * Zoom);
    }

void Charecter:: maybeEatFruite (int xFr, int yFr)
    {
    if ((x_[0] == xFr) && (y_[0] == yFr))
        {
        length_ = length_ + 1;
        /*xFr = rand() % 100 * Zoom;
        yFr = rand() % 50  * Zoom;*/
        }
    }

void numberXchange (int *x, int *y, Charecetr *Snake)
    {
    while (*x != x_[i] && *x%5 == 0 && *y != y_[i] && *y%5 == 0)
        {
        *x = rand() % 100 * Zoom;
        *y = rand() % 100 * Zoom;
        }
    }



