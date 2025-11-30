#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "formuli.h"

int main() {
    double a, b, eps;
    unsigned int fixed_n[] = {10, 100, 1000, 10000};
    unsigned int N = 2;
    int choice;
    double I1, I2, delta, final_result;

    printf("Enter left boundary a: ");
    scanf("%lf", &a);

    printf("Enter right boundary b: ");
    scanf("%lf", &b);

    do {
        printf("Enter accuracy epsilon (0.00001 <= eps <= 0.001): ");
        scanf("%lf", &eps);
        if (eps < 0.00001 || eps > 0.001)
            printf("Error: epsilon must be in range [0.00001, 0.001]\n");
    } while (eps < 0.00001 || eps > 0.001);

    printf("\nChoose method of calculation:\n");
    printf("  1. Left rectangles\n");
    printf("  2. Right rectangles\n");
    printf("  3. Trapezoid\n");
    printf("  4. Parabola (Simpson)\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    printf("\nMethod%-15s| %-10s | %-10s | %-10s | %-10s\n",
           "", "n=10", "n=100", "n=1000", "n=10000");

    switch (choice) {
        case 1:
            printf("Left rectangles    ");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf ", integral_left(a, b, fixed_n[i]));
            printf("\n");
            break;
        case 2:
            printf("Right rectangles   ");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf ", integral_right(a, b, fixed_n[i]));
            printf("\n");
            break;
        case 3:
            printf("Trapezoid          ");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf ", integral_trapezoid(a, b, fixed_n[i]));
            printf("\n");
            break;
        case 4:
            printf("Parabola (Simpson) ");
            for (int i = 0; i < 4; i++)
                printf("| %-10.6lf ", integral_simpson(a, b, fixed_n[i]));
            printf("\n");
            break;
        default:
            printf("Invalid choice.\n");
            return 0;
    }

    printf("\n=== Accuracy analysis ===\n");

    do {
        switch (choice) {
            case 1:
                I1 = integral_left(a, b, N);
                I2 = integral_left(a, b, N + 2);
                break;
            case 2:
                I1 = integral_right(a, b, N);
                I2 = integral_right(a, b, N + 2);
                break;
            case 3:
                I1 = integral_trapezoid(a, b, N);
                I2 = integral_trapezoid(a, b, N + 2);
                break;
            case 4:
                I1 = integral_simpson(a, b, N);
                I2 = integral_simpson(a, b, N + 2);
                break;
        }

        delta = fabs(I1 - I2);
        printf("N = %-3u | I1 = %-10.6lf | I2 = %-10.6lf | Delta = %.8lf\n",
               N, I1, I2, delta);
        N += 2;
    } while (delta > eps);

    N -= 2;

    printf("\nMinimum N found: %u (Delta ≤ %.8lf)\n", N, eps);

    switch (choice) {
        case 1: final_result = integral_left(a, b, N); break;
        case 2: final_result = integral_right(a, b, N); break;
        case 3: final_result = integral_trapezoid(a, b, N); break;
        case 4: final_result = integral_simpson(a, b, N); break;
    }

    printf("Final integral value at N=%u: %.10lf\n", N, final_result);

    printf("\nPress any key to continue...");
    getchar(); getchar();
    return 0;
}
