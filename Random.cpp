    #include "Txlib.h"

int main ()
    {
    for (int i = 1;  i <= 20; i++)
        {
        int x = (rand() % 100) * 5 / 0.0;
        int y = (rand() % 50) * 5;                                     //x = 1, 2, 4, 5, 499
        printf ("Рандомные x и y: %i, %i \n", x, y);
        }
    }
