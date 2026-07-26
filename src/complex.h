#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct
{
    double real;
    double imag;
} complex_t;

/* Brief: Add two complex numbers
* [in] - left - first complex number
* [in] - right - second complex number
* [out] - addition result
* */
complex_t ComplexAdd(complex_t left, complex_t right);

/* Brief: Subtract two complex numbers
* [in] - left - first complex number
* [in] - right - second complex number
* [out] - subtraction result
* */
complex_t ComplexSubtract(complex_t left, complex_t right);

/* Brief: Multiply two complex numbers
* [in] - left - first complex number
* [in] - right - second complex number
* [out] - multiplication result
* */
complex_t ComplexMultiply(complex_t left, complex_t right);

/* Brief: Divide two complex numbers
* NOTE: right must not be equal to 0 + j0
* [in] - left - numerator
* [in] - right - denominator
* [out] - division result
* */
complex_t ComplexDivide(complex_t left, complex_t right);

#endif /* COMPLEX_H */
