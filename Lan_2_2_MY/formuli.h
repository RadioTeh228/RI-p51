#include <stdio.h>
#include <math.h>

#ifndef FORMULI_H_
#define FORMULI_H_

// Підінтегральна функція
double integrand_expression(double x) {
    return 1.0 / (x * x - 1.0);
}

// Метод лівих прямокутників
double integral_left(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (unsigned int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += integrand_expression(x);
    }
    return sum * h;
}

// Метод правих прямокутників
double integral_right(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (unsigned int i = 1; i <= n; i++) {
        double x = a + i * h;
        sum += integrand_expression(x);
    }
    return sum * h;
}

// Метод трапецій
double integral_trapezoid(double a, double b, unsigned int n) {
    double h = (b - a) / n;
    double sum = (integrand_expression(a) + integrand_expression(b)) / 2.0;
    for (unsigned int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += integrand_expression(x);
    }
    return sum * h;
}

// Метод Сімпсона
double integral_simpson(double a, double b, unsigned int n) {
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double sum = integrand_expression(a) + integrand_expression(b);
    for (unsigned int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2 * integrand_expression(x);
        else
            sum += 4 * integrand_expression(x);
    }
    return sum * h / 3.0;
}

#endif
