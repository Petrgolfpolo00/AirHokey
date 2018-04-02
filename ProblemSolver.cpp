    #include "Txlib.h"

void Transport (double* x, double* y);
void Zamena (double* x, double* y);
void ZamenaY (double x, double* y);
double VozvratSum (double x, double y);
double Useless (double* x, double* y);
double UselessCover (const double* x, const double* y);
int main ()
    {
    double x, y;                                                               //преднамеренная ошибка - специально не присваеваем значения
    printf ("до присвоения перменной значения: %lf, %lf \n", x, y);
    Transport (&x, &y);
    printf ("после присвоения перемонной значения: %lf, %lf \n", x, y);
    /*Zamena (&x, &y);
    printf ("после обмена значениями: %lf, %lf \n", x, y);
    ZamenaY (x, &y);
    printf ("после присвоения значения x y: %lf, %lf \n", x, y);
    double sum = VozvratSum (x, y);
    printf ("после возврата суммы, x и y: %lf, %lf, %lf \n", x, y, sum);
    sum = Useless (&x, &y);
    printf ("после возврата суммы, x и y и обнуления: %lf, %lf, %lf \n", x, y, sum);*/
    double sum = UselessCover (&x, &y);
    printf ("после возврата суммы, x и y и обнуления но с работой защиты: %lf, %lf, %lf \n", x, y, sum);

    double* psevdoX = &x;
    double* psevdoY = &y;
    printf (" psevdoX = %d (адрес числа x), там лежит конкретное число %lf \n psevdoY = %d (адрес числа y), там лежит конкрутное чилсо %lf \n", psevdoX, *psevdoX, psevdoY, *psevdoY);
    }

void  Transport (double* x, double* y)
    {
    *x = 5;
    *y = 10;
    }

void Zamena (double*x, double*y)
    {
    double exchenge = *x;
    *x = *y;
    *y = exchenge;
    }

void ZamenaY (double x, double*y)
    {
    *y = x;
    }

double VozvratSum (double x, double y)
    {
    double sum = x + y;
    return sum;
    }

double Useless (double*x, double*y)
    {
    double sum = *x + *y;
    *x = 0;
    *y = 0;
    return sum;
    }

double UselessCover (const double*x, const double*y)
    {
    double sum = *x + *y;
    /**x = 0;
    *y = 0;*/
    return sum;
    }
