    #include "Txlib.h"

const int SnakeSz = 100;
const int Zoom = 5;
const int Head = 25;

struct Charecter
    {
    private:

    int length_;

    int x_[SnakeSz], y_[SnakeSz], vx_, vy_;

    public:

    Charecter (int xUser, int yUser, int vxUser, int vyUser);

    HDC photo_;

    void charecterDraw ();
    void physics (int dt);
    void control ();
    int maybeEatFruite (int xFr, int yFr);
    int matchCheck (int x, int y);
    int gameOver ();
    };

void MainCycle ();
void DrawFruite (int x, int y, HDC frute, int choice);
void numberXchange (int *x, int *y, Charecter *Snake);
void mainMenu ();


int main ()
    {
    _txConsoleMode = SW_SHOW;

    txCreateWindow (100 * Zoom, 100 * Zoom);

    mainMenu ();
    }

void MainCycle ()
    {
    Charecter snake (50 * Zoom, 50 * Zoom, 0 * Zoom, 0 * Zoom);

    int dt = 1;
    int xFr = 0;
    int yFr = 0;
    int choice = 0;

    HDC frute = txLoadImage ("Victim.bmp");

    numberXchange (&xFr, &yFr, &snake);


    while ( ! GetAsyncKeyState (VK_RETURN))
        {
        txSetFillColor (TX_WHITE);
        txClear ();

        DrawFruite (xFr, yFr, frute, choice);

        snake.control ();
        snake.physics (dt);
        snake.charecterDraw ();
        if (snake.gameOver () == 1)
            {
            break;
            }

        if (snake.maybeEatFruite (xFr, yFr) == 1)
            {
            choice = rand() % 3;
            numberXchange (&xFr, &yFr, &snake);
            }

        txSleep (100);
        }

    txDeleteDC (snake.photo_);

    }

Charecter:: Charecter (int xUser, int yUser, int vxUser, int vyUser) :

    x_ ({xUser}),
    y_ ({yUser}),

    vx_ (vxUser),
    vy_ (vyUser),

    photo_ (txLoadImage ("Yota.bmp")),

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

    if (x_[0] > 100 * Zoom)
        {
        x_[0] = 0;
        }

    if (x_[0] < 0)
        {
        x_[0] = 100 * Zoom;
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
    if (GetAsyncKeyState (VK_RIGHT) && vx_ == 0)
        {
        vx_ = 5 * Zoom;
        vy_ = 0;
        }

    if (GetAsyncKeyState (VK_LEFT) && vx_ == 0)
        {
        vx_ = -5 * Zoom;
        vy_ = 0;
        }

    if (GetAsyncKeyState (VK_UP) && vy_ == 0)
        {
        vy_ = -5 * Zoom;
        vx_ = 0;
        }

    if (GetAsyncKeyState (VK_DOWN) && vy_ == 0)
        {
        vy_ = 5 * Zoom;
        vx_ = 0;
        }
    }

void Charecter:: charecterDraw ()
    {
    txSetFillColor (TX_BLUE);
    for (int i = 1; i < length_; i++) txRectangle (x_[i] - 5 * 0.5 * Zoom, y_[i] - 5 * 0.5 * Zoom, x_[i] + 5 * 0.5 * Zoom, y_[i] + 5 * 0.5 * Zoom);

    if (vx_ >= 0 && vy_ == 0) txBitBlt (txDC(), x_[0] - 5 * 0.5 * Zoom, y_[0] - 5 * 0.5 * Zoom, Head, 0, photo_, 25);
    if (vx_ <  0 && vy_ == 0) txBitBlt (txDC(), x_[0] - 5 * 0.5 * Zoom, y_[0] - 5 * 0.5 * Zoom, Head, 0, photo_, 75);
    if (vx_ == 0 && vy_ >  0) txBitBlt (txDC(), x_[0] - 5 * 0.5 * Zoom, y_[0] - 5 * 0.5 * Zoom, Head, 0, photo_, 50);
    if (vx_ == 0 && vy_ <  0) txBitBlt (txDC(), x_[0] - 5 * 0.5 * Zoom, y_[0] - 5 * 0.5 * Zoom, Head, 0, photo_, 0);

    }

void DrawFruite (int x, int y, HDC frute, int  choice)
    {
    txBitBlt (txDC(), x - 12.5, y - 12.5, Head, 0, frute, 25*choice);
    }

int Charecter:: maybeEatFruite (int xFr, int yFr)
    {
    if ((x_[0] == xFr) && (y_[0] == yFr))
        {
        length_ = length_ + 1;
        return 1;
        }
    return 0;
    }

void numberXchange (int *x, int *y, Charecter *snake)
    {
    printf ("Начинается функция создания новых координат, \n");

    do
        {
        *x = (rand() % 18 + 1) * Zoom * 5;                    // Берем координаты нарисованного фрук
        *y = (rand() % 18 + 1) * Zoom * 5;                    // Генирируем новые (рандомные кратные пяти) координаты фрукта
        }                                                     // Сравниваем с координатами змейки
    while (snake->matchCheck (*x, *y) != 0);                  // Если совпало, генирируем новые координаты

    printf ("Новые значения x и y: %i, %i, \n", *x, *y);
    }

int Charecter:: matchCheck (int x,int y)
    {
    for (int i = 0; i <= length_ - 1; i++)
        {
        if ((x_[i] == x) && (y_[i] == y))
            {
            return 1;
            }
        return 0;
        }
    }

int Charecter:: gameOver ()
    {
    if (length_ < 5)
        {
        return 0;
        }

    for (int i = 1; i < length_; i++)
        {                                                        // i = 0,  1,  2, 3,  4, 5
        if (x_[0] == x_[i] && y_[0] == y_[i])                    // x = 5  10  10  5  10  5
            {                                                    // y = 10 15  20 15  15 10
            txClear ();
            txSetTextAlign ();
            txTextOut (500, 250, "GAME OVER");
            return 1;
            }
        }
    return 0;
    }

void mainMenu ()
    {
    HDC menu = txLoadImage ("MenuDraw.bmp");
    txBitBlt (txDC(), 0, 0, 0, 0, menu);

    if ((txMousePos(), 139, 115, 320, 179) && (txMouseButtons() & 1))
        {
        txClear ();
        MainCycle ();
        }

    txDeleteDC (menu);
    }


