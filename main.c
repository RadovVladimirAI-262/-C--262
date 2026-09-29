#include <stdio.h>
#include <math.h>
#include <windows.h>

#define EPS   1e-9   // Точность сравнения вещественных чисел
#define DELTA 1e-6   // Поправка при вычислении количества шагов

int main()
{
    // Настройка консоли для русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double a, b, c;
    double xn, xk, dx;
    double x, F;
    long Ac, Bc, Cc;   // Целые части a, b, c
    int veshch;        // Флаг вывода (1 = действительное F, 0 = целое F)
    int i, n;          // i = счетчик цикла, n = количество шагов
    int k;             // Количество успешно введенных значений

    printf("Введите значения:\n");
    printf("\ta = ");           k  = scanf("%lf", &a);
    printf("\tb = ");           k += scanf("%lf", &b);
    printf("\tc = ");           k += scanf("%lf", &c);
    printf("\tX начальное = "); k += scanf("%lf", &xn);
    printf("\tX конечное  = "); k += scanf("%lf", &xk);
    printf("\tdX = ");          k += scanf("%lf", &dx);

    // Проверка исходных данных: введены числа, шаг не нулевой
    // и направлен от X начального к X конечному
    if (k != 6 || fabs(dx) < EPS || (xk - xn) / dx < 0)
    {
        printf("Ошибка: некорректные исходные данные.\n");
        return 1;
    }

    // Отбрасывание дробной части для поразрядных операций
    Ac = (long)a;
    Bc = (long)b;
    Cc = (long)c;

    // Условие задания: (Ац ИЛИ Вц) И (Ац ИЛИ Сц) не равно нулю
    if (((Ac | Bc) & (Ac | Cc)) != 0)
        veshch = 1;
    else
        veshch = 0;

    // Количество шагов табулирования
    n = (int)((xk - xn) / dx + DELTA);

    printf("\n       X          F\n");
    printf("---------------------\n");

    // Главный цикл: шаги от 0 до n включительно
    for (i = 0; i <= n; i++)
    {
        x = xn + i * dx;   // Текущее значение X

        if (a < 0 && c != 0)
        {
            F = a * x * x + b * x + c;
        }
        else if (a > 0 && b == 0)
        {
            if (fabs(x - c) < EPS)   // Защита от деления на ноль
            {
                printf("%8.2f   не определено\n", x);
                continue;
            }
            F = -a / (x - c);
        }
        else
        {
            F = a * (x + c);
        }

        // Вывод результата в зависимости от флага veshch
        if (veshch)
            printf("%8.2f %10.3f\n", x, F);        // Действительное значение
        else
            printf("%8.2f %10ld\n", x, (long)F);   // Целое значение
    }

    printf("---------------------\n");

    return 0;
}
