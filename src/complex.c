#include <assert.h>

#include "complex.h"

complex_t ComplexAdd(complex_t left, complex_t right)
{
    complex_t result;

    result.real = left.real + right.real;
    result.imag = left.imag + right.imag;

    return result;
}

complex_t ComplexSub(complex_t left, complex_t right)
{
    complex_t result;

    result.real = left.real - right.real;
    result.imag = left.imag - right.imag;

    return result;
}

complex_t ComplexMul(complex_t left, complex_t right)
{
    complex_t result;

    /*
     * (a + jb) * (c + jd)
     *
     * real = ac - bd
     * imag = ad + bc
     */
    result.real = left.real * right.real - left.imag * right.imag;
    result.imag = left.real * right.imag + left.imag * right.real;

    return result;
}

complex_t ComplexDiv(complex_t left, complex_t right)
{
    complex_t result;
    double denominator;

    /*
     * (a + jb) / (c + jd)
     *
     * real = (ac + bd) / (c^2 + d^2)
     * imag = (bc - ad) / (c^2 + d^2)
     */
    denominator = right.real * right.real + right.imag * right.imag;
    assert(denominator != 0.0);

    result.real = (left.real * right.real + left.imag * right.imag) / denominator;
    result.imag = (left.imag * right.real - left.real * right.imag) / denominator;

    return result;
}
