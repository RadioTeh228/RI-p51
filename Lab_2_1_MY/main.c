#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    double x, y; // оголошення змінних

    printf("Enter x: "); // запит користувачу
    scanf("%lf", &x);    // введення значення x

    // ---- обчислення y(x) для різних діапазонів ----
    if (x >= -15 && x < -5)
        y = pow(x, 3) + 2 * pow(x, 2);     // y = x³ + 2x²
    else if (x >= 2 && x < 18)
        y = 5;                             // y = 5 (константа)
    else if (x >= 58 && x < 104)
        y = sqrt(x * x + 10 * x);          // y = √(x² + 10x)
    else
        y = -2 - x / 25;                   // y = -2 − x/25 (інші випадки)

    // ---- вивід результату ----
    printf("For x = %.6f, y = %.6f\n", x, y);

    return 0;
}
