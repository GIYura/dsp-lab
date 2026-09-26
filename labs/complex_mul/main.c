/*
 * Complex multiplication demo
 * */

#include <stdio.h>

#include "complex.h"

int main(void)
{
    complex_t a;
    complex_t b;
    complex_t c;

    double k1, k2, k3, r, i;

    a.imag = 1;
    a.real = 2;

    b.imag = 2;
    b.real = 1;

    c = ComplexMul(a, b);

    printf("I=%f R=%f\n", c.imag, c.real);

    k1 = a.real * (b.real + b.imag);
    k2 = b.imag * (a.real + a.imag);
    k3 = b.real * (a.imag - a.real);

    r = k1 - k2;
    i = k1 + k3;

    printf("I=%f R=%f\n", i, r);

    return 0;
}
